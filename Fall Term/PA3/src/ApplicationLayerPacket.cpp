#include "ApplicationLayerPacket.h"

ApplicationLayerPacket::ApplicationLayerPacket(int _layer_ID, const string &_sender_ID, const string &_receiver_ID, const string& _message_data) : Packet(_layer_ID) {
    sender_ID = _sender_ID;
    receiver_ID = _receiver_ID;
    message_data = _message_data;
}

void ApplicationLayerPacket::print() {
    std::cout << "Sender ID: " << sender_ID << ", Receiver ID: " << receiver_ID << "\n";
    // TODO: Override the virtual print function from Packet class to additionally print layer-specific properties.
}

ApplicationLayerPacket::~ApplicationLayerPacket() {
    // TODO: Free any dynamically allocated memory if necessary.
}

string ApplicationLayerPacket::getMessageData() const {
    return message_data;
}

string ApplicationLayerPacket::getReceiverID() const {
    return receiver_ID;
}

string ApplicationLayerPacket::getSenderID() const {
    return sender_ID;
}
