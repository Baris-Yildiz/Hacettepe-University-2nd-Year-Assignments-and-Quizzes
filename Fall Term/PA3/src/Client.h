#ifndef SRC_CLIENT_H
#define SRC_CLIENT_H

#include <string>
#include <unordered_map>
#include <ostream>
#include <stack>
#include <queue>
#include <vector>
#include <bits/stdc++.h>

#include "Packet.h"
#include "ApplicationLayerPacket.h"
#include "TransportLayerPacket.h"
#include "NetworkLayerPacket.h"
#include "PhysicalLayerPacket.h"
#include "Log.h"

using namespace std;

class Client {
public:
    Client(string const& id, string const& ip, string const& mac);
    ~Client();

    string client_id;
    string client_ip;
    string client_mac;
    vector<Log> log_entries;
    unordered_map < string, string > routing_table; // <receiverID, nexthopID>
    queue<stack<Packet*>> incoming_queue;
    queue<stack<Packet*>> outgoing_queue;

    friend ostream &operator<<(ostream &os, const Client &client);

    void messageClient(vector<Client> &clients, Client &destination, string message,
                  int messageLimit, const string &senderPort, const string &receiverPort);

    void createAndEnqueueNewFrame(const string &message, const Client &sender, const string& senderPort,
                                  const string& receiverPort, vector<Client>& clients, int frameNumber);

    void showFrameInfo(const string& queue, int frameNumber);
    void showQueueInfo(const string& queue);

    void forwardMessage(vector<Client> &clients);

    void receiveMessage(vector<Client> &vector);

    void printLog();

    void createLog(const string &message, int number_of_frames, int number_of_hops, const string& sender_id,
                   const string &receiver_id, bool success, ActivityType type);

private:

    stack<Packet*> retrieveFrameFromQueue(int frame, queue<stack<Packet *>> queue);
    void printLayerInformation(stack<Packet *> frame);

    pair<queue<stack<Packet*>>, string> getQueue(const string& queue);

    bool checkIfLastChunk(string message);

    ApplicationLayerPacket* printFrameInformation(stack<Packet *> frame);

    Client* getClientFromMACAddress(vector<Client>& clients, const string& mac);
    Client* getClientFromID(vector<Client>& clients, const string& id);

    bool clientExists(string clientID, vector<Client>& clients);

    void deleteFrame(stack<Packet *> &frame);


};


#endif //SRC_CLIENT_H
