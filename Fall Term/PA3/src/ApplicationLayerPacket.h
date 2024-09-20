#ifndef APPLICATION_LAYER_PACKET_H
#define APPLICATION_LAYER_PACKET_H

#include "Packet.h"

// Extends Packet class. Have additional layer-specific member variables and overrides the virtual print function.
class ApplicationLayerPacket : public Packet {
public:
    ApplicationLayerPacket(int _layer_ID, const string& _sender_ID, const string& _receiver_ID, const string& _message_data);
    ~ApplicationLayerPacket() override;

    string sender_ID;
    string receiver_ID;
    string message_data;

    void print() override;

    // Getter methods for fields.
    string getMessageData() const;
    string getReceiverID() const;
    string getSenderID() const;
};

#endif // APPLICATION_LAYER_PACKET_H
