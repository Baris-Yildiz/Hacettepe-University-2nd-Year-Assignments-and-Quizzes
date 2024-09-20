#include "Packet.h"
#include <iostream>

Packet::Packet(int _layer_ID) {
    layer_ID = _layer_ID;
    hops = 0;
}


ostream& operator<<(ostream& os, const Packet& packet) {
    os << "Packet layer: " << packet.layer_ID;
    return os;
}

Packet::~Packet() {
    // TODO: Free any dynamically allocated memory if necessary.
}