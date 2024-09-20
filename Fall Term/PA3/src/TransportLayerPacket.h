#ifndef TRANSPORT_LAYER_PACKET_H
#define TRANSPORT_LAYER_PACKET_H

#include "Packet.h"

// Extends Packet class. Have additional layer-specific member variables and overrides the virtual print function.
class TransportLayerPacket : public Packet {

public:
    TransportLayerPacket(int _layer_ID, string _sender_port, string _receiver_port);
    ~TransportLayerPacket() override;

    string sender_port_number;
    string receiver_port_number;

    void print() override;
};

#endif // TRANSPORT_LAYER_PACKET_H
