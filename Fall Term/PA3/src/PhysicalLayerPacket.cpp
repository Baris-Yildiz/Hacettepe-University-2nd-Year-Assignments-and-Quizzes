#include "PhysicalLayerPacket.h"

PhysicalLayerPacket::PhysicalLayerPacket(int _layer_ID, const string& _sender_MAC, const string& _receiver_MAC)
        : Packet(_layer_ID) {
    sender_MAC_address = _sender_MAC;
    receiver_MAC_address = _receiver_MAC;
}

void PhysicalLayerPacket::print() {
    std::cout << "Sender MAC address: " << sender_MAC_address << ", Receiver MAC address: " << receiver_MAC_address << "\n";
    // TODO: Override the virtual print function from Packet class to additionally print layer-specific properties.
}

PhysicalLayerPacket::~PhysicalLayerPacket() {
    // TODO: Free any dynamically allocated memory if necessary.
}

string PhysicalLayerPacket::getReceiverMacAddress() {
    return receiver_MAC_address;
}

string PhysicalLayerPacket::getSenderMacAddress() {
    return sender_MAC_address;
}

void PhysicalLayerPacket::setSenderMacAddress(const string &newMac){
    sender_MAC_address = newMac;
}

void PhysicalLayerPacket::setReceiverMacAddress(const string &newMac) {
    receiver_MAC_address = newMac;
}
