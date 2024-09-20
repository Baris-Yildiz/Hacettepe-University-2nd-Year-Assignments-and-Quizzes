#include "Network.h"
#include "fstream"

Network::Network() {

}

Network::~Network() {
    // TODO: Free any dynamically allocated memory if necessary.
}

/* Executes every command given in the "commands" vector.*/
void Network::process_commands(vector<Client> &clients, vector<string> &commands, int message_limit,
                      const string &sender_port, const string &receiver_port) {

    for (const string& command: commands) {

        printCommandDisplay(command);
        stringstream commandStream(command);

        string keyword;
        getline(commandStream, keyword, ' ');

        if (keyword == "MESSAGE") {
            string clientID;
            string receiverID;
            string message;

            getline(commandStream, clientID, ' ');
            getline(commandStream, receiverID, ' ');
            getline(commandStream, message);

            message = message.substr(1, message.length()-2);

            getClient(clientID, clients)->messageClient(clients,
                                                        *getClient(receiverID, clients),
                                                        message,
                                                        message_limit,
                                                        sender_port,
                                                        receiver_port);

        } else if (keyword == "SHOW_FRAME_INFO") {
            string clientID;
            getline(commandStream, clientID, ' ');

            string queueType;
            getline(commandStream, queueType, ' ');

            string frameNumber;
            getline(commandStream, frameNumber);

            getClient(clientID, clients)->showFrameInfo(queueType, stoi(frameNumber));
        } else if (keyword == "SHOW_Q_INFO") {
            string clientID;
            getline(commandStream, clientID, ' ');

            string queueType;
            getline(commandStream, queueType);

            getClient(clientID, clients)->showQueueInfo(queueType);

        } else if (keyword == "SEND") {
            for (Client& client: clients) {
                client.forwardMessage(clients);
            }
        } else if (keyword == "RECEIVE") {
            for (Client& client: clients) {
                client.receiveMessage(clients);
            }
        } else if (keyword == "PRINT_LOG") {
            string clientID;
            getline(commandStream, clientID);

            getClient(clientID, clients)->printLog();
        } else {
            std::cout << "Invalid command.\n";
        }

    }

    // TODO: Execute the commands given as a vector of strings while utilizing the remaining arguments.
    /* Don't use any static variables, assume this method will be called over and over during testing.
     Don't forget to update the necessary member variables after processing each command. For example,
     after the MESSAGE command, the outgoing queue of the sender must have the expected frames ready to send. */
}

/* Reads clients from a file and returns a client list. */
vector<Client> Network::read_clients(const string &filename) {
    vector<Client> clients;
    ifstream clientFile(filename);

    if (!clientFile.is_open()) {
        std::cout << "Cannot open the file containing client information." << std::endl;
        return clients;
    }

    std::string line;

    getline(clientFile, line);
    int numberOfClients = stoi(line);

    for (int i = 0; i < numberOfClients; i++) {
        Client newClient = readClient(clientFile);
        clients.push_back(newClient);
    }

    clientFile.close();
    return clients;
}
/* Reads the routing tables from an input file, assigns them to every client in "clients".*/
void Network::read_routing_tables(vector<Client> &clients, const string &filename) {
    ifstream routingFile(filename);

    if (!routingFile.is_open()) {
        std::cout << "Cannot open the file containing routing tables." << std::endl;
        return;
    }

    for (int i = 0; i < clients.size(); i++) {
        addRoutingInformationToClient(clients[i], routingFile);
    }
}

// Returns a list of token lists for each command
vector<string> Network::read_commands(const string &filename) {
    vector<string> commands;
    ifstream commandFile(filename);

    if (!commandFile.is_open()) {
        std::cout << "Cannot open file containing commands." << std::endl;
        return commands;
    }

    string line;

    getline(commandFile, line);
    int numberOfCommands = stoi(line);

    for (int i = 0; i < numberOfCommands; i++) {
        getline(commandFile, line);
        commands.push_back(line);
    }

    return commands;
}

/* Reads a single client from the current file position.*/
Client Network::readClient(ifstream &file) {
    string clientID;
    getline(file, clientID, ' ');

    string clientIP;
    getline(file, clientIP, ' ');

    string clientMAC;
    getline(file, clientMAC);

    Client client(clientID, clientIP, clientMAC);
    return client;
}

/* Assigns routing table to a client.*/
void Network::addRoutingInformationToClient(Client &client, ifstream &file) {
    string line;

    while(getline(file, line) && line != "-") {
        stringstream stream(line);

        string finalDestination;
        getline(stream, finalDestination, ' ');

        string forwardDestination;
        getline(stream, forwardDestination);

        client.routing_table[finalDestination] = forwardDestination;
    }
}
/* Prints the generic command template. */
void Network::printCommandDisplay(const string& command) {
    for (int i = 0; i < command.size() + 9; i++) {
        std::cout << "-";
    }
    std::cout << "\nCommand: " << command << "\n";

    for (int i = 0; i < command.size() + 9; i++) {
        std::cout << "-";
    }
    std::cout << "\n";
}

/* Returns the client from "clients" whose ID is "clientID". */
Client *Network::getClient(const string &clientID, vector<Client> &clients) {
    for (Client& client: clients) {
        if (client.client_id == clientID) {
            return &client;
        }
    }
    return nullptr;
}