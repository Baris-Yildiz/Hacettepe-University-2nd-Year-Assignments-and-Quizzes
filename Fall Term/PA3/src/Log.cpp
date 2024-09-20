//
// Created by alperen on 2.10.2023.
//

#include "Log.h"

/* Constructor for Log instantiates fields. */
Log::Log(const string &_timestamp, const string &_message, int _number_of_frames, int _number_of_hops, const string &_sender_id,
         const string &_receiver_id, bool _success, ActivityType _type) {
    timestamp = _timestamp;
    message_content = _message;
    number_of_frames = _number_of_frames;
    number_of_hops = _number_of_hops;
    sender_id = _sender_id;
    receiver_id = _receiver_id;
    success_status = _success;
    activity_type = _type;
}

Log::~Log() {
    // TODO: Free any dynamically allocated memory if necessary.
}

/* Prints the log into std::cout. */
void Log::print() const {
    string status;

    if (activity_type == ActivityType::MESSAGE_FORWARDED) {
        status = "Forwarded";
    } else if (activity_type == ActivityType::MESSAGE_DROPPED) {
        status = "Dropped";
    } else if (activity_type == ActivityType::MESSAGE_RECEIVED) {
        status = "Received";
    } else {
        status = "Sent";
    }

    std::cout << "Activity: Message " << status;

    std::cout << "\nTimestamp: " << convertTimestampToDate()
              << "\nNumber of frames: " << number_of_frames
              << "\nNumber of hops: " << number_of_hops
              << "\nSender ID: " << sender_id
              << "\nReceiver ID: " << receiver_id
              << "\nSuccess: " << (success_status ? "Yes" : "No");


    if (activity_type == ActivityType::MESSAGE_RECEIVED || activity_type == ActivityType::MESSAGE_SENT) {
        std::cout << "\nMessage: \"" << message_content << "\"";
    }

    std::cout << std::endl;
}

/* Formats the timestamp field into a human-readable date. */
string Log::convertTimestampToDate() const {

    auto time = (time_t)(stoll(timestamp));

    char date[20];
    strftime(date, 20, "%Y-%m-%d %H:%M:%S", localtime(&time));

    return date;
}


