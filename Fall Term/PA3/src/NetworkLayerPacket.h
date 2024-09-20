#ifndef NETWORK_LAYER_PACKET_H
#define NETWORK_LAYER_PACKET_H

#include "Packet.h"

// Extends Packet class. Have additional layer-specific member variables and overrides the virtual print function.
class NetworkLayerPacket : public Packet {
public:
    NetworkLayerPacket(int _layer_ID, const string& _sender_IP, const string& _receiver_IP);
    ~NetworkLayerPacket() override;

    string sender_IP_address;
    string receiver_IP_address;

    void print() override;
};

#endif // NETWORK_LAYER_PACKET_H
