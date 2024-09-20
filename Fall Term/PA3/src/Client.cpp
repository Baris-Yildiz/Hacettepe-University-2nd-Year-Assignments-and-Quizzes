//
// Created by alperen on 27.09.2023.
//

#include "Client.h"

// Constructor for Client initializes fields.
Client::Client(string const& _id, string const& _ip, string const& _mac) {
    client_id = _id;
    client_ip = _ip;
    client_mac = _mac;
}

ostream &operator<<(ostream &os, const Client &client) {
    os << "client_id: " << client.client_id << " client_ip: " << client.client_ip << " client_mac: "
       << client.client_mac << endl;
    return os;
}

/* Destructor for Client checks if any queues hold dynamically created objects. This can
 * happen in case a message was on its way to destination when the program execution stops. */
Client::~Client() {
    while (!incoming_queue.empty()) {
        stack<Packet*>& frame = incoming_queue.front();
        while (!frame.empty()) {
            delete frame.top();
            frame.pop();
        }
        incoming_queue.pop();
    }

    while (!outgoing_queue.empty()) {
        stack<Packet*>& frame = outgoing_queue.front();
        while (!frame.empty()) {
            delete frame.top();
            frame.pop();
        }
        outgoing_queue.pop();
    }
}


/* The method called by the MESSAGE command. Initiates the messaging procedure by splitting the message to chunks
 * and placing the frames consisting of these chunks to the sender's outgoing queue. */
void Client::messageClient(vector<Client>& clients, Client& destination, string message,
                           int messageLimit, const string& senderPort, const string& receiverPort) {
    string fullMessage = message;
    std::cout << "Message to be sent: \"" << message << "\"\n\n";
    int frameIndex = 1;

    while (!message.empty() && message.length() >= messageLimit) {

        string messageToBeSent = message.substr(0,messageLimit);
        message.erase(0, messageLimit);

        createAndEnqueueNewFrame(messageToBeSent, destination, senderPort,
                                        receiverPort, clients, frameIndex++);
    }

    if (!message.empty()) {
        createAndEnqueueNewFrame(message, destination,
                                        senderPort, receiverPort, clients, frameIndex++);
    }

    createLog(fullMessage, frameIndex-1, 0,
                     client_id,
                     destination.client_id, true,ActivityType::MESSAGE_SENT);

}

/* Creates a frame that contains various information in the form of "Packets" about the sending process. */
void Client::createAndEnqueueNewFrame(const string &message, const Client &receiver, const string &senderPort,
                            const string &receiverPort, vector<Client>& clients, int frameNumber) {
    std::cout << "Frame #" << frameNumber << "\n";

    string receiverID = routing_table[receiver.client_id];
    Client* currentReceiver = getClientFromID(clients, receiverID);

    Packet* packets[4] = {new ApplicationLayerPacket(0,client_id,receiver.client_id,message),
                          new TransportLayerPacket(1, senderPort, receiverPort),
                          new NetworkLayerPacket(2, client_ip, receiver.client_ip),
                          new PhysicalLayerPacket(3, client_mac, currentReceiver->client_mac)};

    stack<Packet*> frame;
    for(auto packet : packets) {
        frame.push(packet);
    }

    printFrameInformation(frame);

    outgoing_queue.push(frame);
}

/* Prints the information contained in the frame.*/
void Client::showFrameInfo(const string &queue, int frame) {

    std::queue<stack<Packet*>> selectedQueue = getQueue(queue).first;
    string queueType = getQueue(queue).second;


    if (selectedQueue.size() < frame) {
        std::cout << "No such frame.\n";
        return;
    }

    std::cout << "Current Frame #" << frame << " on the " << queueType <<
    " queue of client " << client_id << "\n";

    printLayerInformation(retrieveFrameFromQueue(frame, selectedQueue));

}

/* Prints information about the number of frames in the queue and the type of the queue. */
void Client::showQueueInfo(const string &queue) {
    std::queue<stack<Packet*>> selectedQueue = getQueue(queue).first;
    string queueType = getQueue(queue).second;

    queueType[0] = (char)toupper(queueType[0]);

    std::cout << "Client " << client_id << " " << queueType << " Queue Status\n" <<
    "Current total number of frames: " << selectedQueue.size() << "\n";
}

/* The method called by the SEND command. Sends the message frames to the next client and prints
 * certain information about it.*/
void Client::forwardMessage(vector<Client> &clients){

    if (outgoing_queue.empty()) {
        return;
    }

    int frameIndex = 1;
    stringstream fullMessage;

    while (!outgoing_queue.empty()) {
        stack<Packet*>& frameRef = outgoing_queue.front();
        std::cout << "Client " << client_id << " sending frame #" << frameIndex++ << " to client ";

        stack<Packet*> frame = frameRef;
        string receiverMAC = ((PhysicalLayerPacket*)frame.top())->getReceiverMacAddress();

        Client* receiver = getClientFromMACAddress(clients, receiverMAC);
        receiver->incoming_queue.push(frameRef);
        std::cout << receiver->client_id << "\n";

        frameRef.top()->hops++;
        ApplicationLayerPacket* applicationLayerPacket = printFrameInformation(frame);
        string message = applicationLayerPacket->getMessageData();
        fullMessage << message;

        if (checkIfLastChunk(message)) {

            fullMessage.str("");
            frameIndex = 1;
        }


        outgoing_queue.pop();
    }

}

/* The method called by the RECEIVE command. Makes the client receive the message and respond to it.
 * If the message was meant for it, assembles and prints the full message. Otherwise, forwards it to
 * the next client on the line. If the next client cannot be found, drops the message.*/
void Client::receiveMessage(vector<Client> &clients) {

    if (incoming_queue.empty()) {
        return;
    }

    int frameIndex = 1;
    stringstream fullMessage;
    bool forwarding = false;

    while (!incoming_queue.empty()) {
        stack<Packet*> frame = incoming_queue.front();
        stack<Packet*>& frameRef = incoming_queue.front();

        string senderMAC = ((PhysicalLayerPacket*)frame.top())->getSenderMacAddress();
        string senderID = getClientFromMACAddress(clients, senderMAC)->client_id;

        for (int i = 0; i < 3; i++) {
            frame.pop();
        }

        auto * applicationLayerPacket = ((ApplicationLayerPacket* )frame.top());
        string receiverID = applicationLayerPacket->getReceiverID();

        if (receiverID == client_id) {

            std::cout << "Client " << client_id << " receiving frame #" << frameIndex++ << " from client "
                      << senderID << ", originating from client " << applicationLayerPacket->getSenderID() << "\n";

            printFrameInformation(frameRef);

            fullMessage << applicationLayerPacket->getMessageData();

            if (checkIfLastChunk(applicationLayerPacket->getMessageData())) {

                createLog(fullMessage.str(), frameIndex-1, frameRef.top()->hops,
                          applicationLayerPacket->getSenderID(),
                          applicationLayerPacket->getReceiverID(), true,ActivityType::MESSAGE_RECEIVED);

                std::cout << "Client " << client_id << " received the message \"" << fullMessage.str()
                << "\" from client " << applicationLayerPacket->getSenderID() << ".\n--------" << std::endl;

                fullMessage.str("");
                frameIndex = 1;
            }

            deleteFrame(frameRef);
            incoming_queue.pop();
            continue;
        }


        if (!routing_table.count(receiverID) || !clientExists(routing_table[receiverID], clients)) {

            std::cout << "Client " << client_id << " receiving frame #" << frameIndex++ << " from client " << senderID
                      << ", but intended for client " << receiverID << ". Forwarding... \n";

            std::cout << "Error: Unreachable destination. Packets are dropped after " << frameRef.top()->hops << " hops!\n";


            if (checkIfLastChunk(applicationLayerPacket->getMessageData())) {

                createLog("", frameIndex-1, frameRef.top()->hops,
                          applicationLayerPacket->getSenderID(), applicationLayerPacket->getReceiverID(),
                          false,ActivityType::MESSAGE_DROPPED);

                frameIndex = 1;
                std::cout << "--------" << std::endl;
            }

            deleteFrame(frameRef);
            incoming_queue.pop();
            continue;

        } else {
            if (!forwarding) {
                std::cout << "Client " << client_id << " receiving a message from client " << senderID
                          << ", but intended for client " << receiverID << ". Forwarding... \n";
            }

            forwarding = true;
            std::cout << "Frame #"<< frameIndex++ << " MAC address change: New sender MAC " <<
                      client_mac <<", new receiver MAC ";

            auto* physicalLayerPacket = ((PhysicalLayerPacket*)(frameRef.top()));
            physicalLayerPacket->setSenderMacAddress(client_mac);

            string forwardToID = routing_table[receiverID];

            Client* forwardToClient = getClientFromID(clients, forwardToID);
            physicalLayerPacket->setReceiverMacAddress(forwardToClient->client_mac);
            std::cout << forwardToClient->client_mac << "\n";

            outgoing_queue.push(frameRef);
        }

        if (checkIfLastChunk(applicationLayerPacket->getMessageData())) {

            createLog("", frameIndex-1, frameRef.top()->hops,
                      applicationLayerPacket->getSenderID(),applicationLayerPacket->getReceiverID(),
                      true,ActivityType::MESSAGE_FORWARDED);

            frameIndex = 1;
            std::cout << "--------" << std::endl;
            forwarding = false;
        }

        incoming_queue.pop();

    }
}

/* Prints all logs of the client. */
void Client::printLog() {
    if (!log_entries.empty()) {
        std::cout << "Client " << client_id << " Logs: \n";
    }

    for (int i = 0; i < log_entries.size(); i++) {
        std::cout << "--------------\n";
        std::cout << "Log Entry #" << i+1 << ":\n";
        log_entries[i].print();
    }
}

/* Creates a new log entry. */
void Client::createLog(const string &message, int number_of_frames, int number_of_hops, const string& sender_id,
                       const string &receiver_id, bool success, ActivityType type) {

    Log log(to_string(time(nullptr)), message, number_of_frames, number_of_hops, sender_id, receiver_id, success, type);
    log_entries.push_back(log);
}

/* Prints the information about a frame to std::cout. */
ApplicationLayerPacket* Client::printFrameInformation(stack<Packet *> frame) {
    int hops = frame.top()->hops;
    for (int i = 0; i < 3; i++) {
        frame.top()->print();
        frame.pop();
    }

    frame.top()->print();
    string message = ((ApplicationLayerPacket*)frame.top())->getMessageData();

    std::cout << "Message chunk carried: \"" << message << "\"\n";
    std::cout << "Number of hops so far: " << hops << "\n--------" << std::endl;
    return ((ApplicationLayerPacket*)frame.top());
}

/* Prints a frame's content with the layer info. Starts from the bottom of the Packet stack.*/
void Client::printLayerInformation(stack<Packet*> frame) {
    stack<Packet*> secondaryStack;
    int hops = frame.top()->hops;

    while (!frame.empty()) {
        secondaryStack.push(frame.top());
        frame.pop();
    }

    auto * applicationLayerPacket = (ApplicationLayerPacket*) secondaryStack.top();
    std::cout << "Carried Message: \"" << applicationLayerPacket->getMessageData() << "\"\n";

    int layerIndex = 0;

    while (!secondaryStack.empty()) {
        std::cout << "Layer " << layerIndex++ << " info: ";
        secondaryStack.top()->print();
        secondaryStack.pop();
    }

    std::cout << "Number of hops so far: " << hops << "\n";
}

/* Returns either the incoming or the outgoing queue based on the parameter "queue".
 * Used as a helper function to quickly retrieve a certain queue. */
pair<queue<stack<Packet *>>, string> Client::getQueue(const string &queue) {
    if (queue != "in" && queue != "out") {
        return {};
    } else if (queue == "in") {
        return {incoming_queue, "incoming"};
    } else {
        return {outgoing_queue, "outgoing"};
    }
}

/* Returns the frame at a certain index in the queue. */
stack<Packet*> Client::retrieveFrameFromQueue(int frame, queue<stack<Packet*>> queue) {
    for (int i = 0; i < frame-1; i++) {
        queue.pop();
    }

    return queue.front();
}

/* Given a client ID, returns the client who has that client ID*/
Client *Client::getClientFromID(vector<Client> &clients, const string &id) {
    for (Client& client : clients) {
        if (id == client.client_id) {
            return &client;
        }
    }

    return nullptr;
}

/* Given a MAC address, returns the client who has that MAC address. */
Client *Client::getClientFromMACAddress(vector<Client> &clients, const string &mac) {

    for (Client& client : clients) {
        if (mac == client.client_mac) {
            return &client;
        }
    }

    return nullptr;
}

/* Checks if the given message ends with a punctuation mark, representing that it is
 * the final chunk of the message. Helper method used by various other methods in Client.*/
bool Client::checkIfLastChunk(string message) {
    char lastCharacter = message[message.length()-1];
    return (lastCharacter == '.' || lastCharacter == '!' || lastCharacter == '?');
}

/*Checks if the client exists in a vector of Clients. */
bool Client::clientExists(string clientID, vector<Client> &clients) {

    for (const Client& client: clients) {
        if (client.client_id == clientID) {
            return true;
        }
    }

    return false;
}

/* Deletes a frame (deallocates memory) This is used when a frame is dropped or
 * the message inside it has reached its final destination.*/
void Client::deleteFrame(stack<Packet*>& frame) {
    while (!frame.empty()) {
        delete frame.top();
        frame.pop();
    }
}