#include "TransportLayerPacket.h"

TransportLayerPacket::TransportLayerPacket(int _layer_ID, string _sender_port, string _receiver_port)
        : Packet(_layer_ID) {
    sender_port_number = _sender_port;
    receiver_port_number = _receiver_port;
}

void TransportLayerPacket::print() {
    std::cout << "Sender port number: " << sender_port_number << ", Receiver port number: " << receiver_port_number << "\n";
    // TODO: Override the virtual print function from Packet class to additionally print layer-specific properties.
}

TransportLayerPacket::~TransportLayerPacket() {
    // TODO: Free any dynamically allocated memory if necessary.
}