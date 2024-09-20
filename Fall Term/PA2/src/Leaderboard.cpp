#include <fstream>
#include <iostream>
#include "Leaderboard.h"
#include "sstream"
#include "ostream"

void Leaderboard::insert_new_entry(LeaderboardEntry * new_entry) {

    LeaderboardEntry* curr = head_leaderboard_entry;

    if (curr == nullptr || new_entry->score > curr->score) {
        new_entry->next_leaderboard_entry = curr;
        head_leaderboard_entry = new_entry;
    } else {
        while (curr->next_leaderboard_entry != nullptr) {
            LeaderboardEntry* comparedEntry = curr->next_leaderboard_entry;

            if (new_entry->score > comparedEntry->score) {
                break;
            }

            curr = curr->next_leaderboard_entry;
        }

        new_entry->next_leaderboard_entry = curr->next_leaderboard_entry;
        curr->next_leaderboard_entry = new_entry;

    }

    if (++entries > 10) {

        LeaderboardEntry* temp = head_leaderboard_entry;

        while (temp->next_leaderboard_entry->next_leaderboard_entry != nullptr) {
            temp = temp->next_leaderboard_entry;
        }

        delete temp->next_leaderboard_entry;
        temp->next_leaderboard_entry = nullptr;

        entries = 10;
    }
}

void Leaderboard::write_to_file(const string& filename) {
    LeaderboardEntry* curr = head_leaderboard_entry;

    ofstream file(filename);

    while (curr != nullptr) {
        file << curr->score << " " << curr->last_played << " " << curr->player_name << "\n";
        curr = curr->next_leaderboard_entry;
    }

    file.flush();
    file.close();

}

void Leaderboard::read_from_file(const string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return;
    }

    string currentRecord;

    while (getline(file, currentRecord)) {
        if (entries == 10) {
            break;
        }

        vector<string> fields = splitString(currentRecord);
        auto* leaderboardEntry = new LeaderboardEntry(stoul(fields[0]), (time_t) stol(fields[1]), fields[2]);

        insert_new_entry(leaderboardEntry);
    }

    file.close();


}


void Leaderboard::print_leaderboard() {
    std::cout << "Leaderboard\n-----------\n";
    LeaderboardEntry* head = head_leaderboard_entry;
    int order = 1;

    while (head != nullptr) {
        time_t time = head->last_played;

        char buffer[20];
        strftime(buffer,20,"%H:%M:%S/%d.%m.%Y", localtime(&time));

        std::cout << order++ << ". " << head->player_name << " " << head->score << " " << buffer << "\n";
        head = head->next_leaderboard_entry;
    }
    std::cout.flush();

}

Leaderboard::~Leaderboard() {
    LeaderboardEntry* temp;

    while (head_leaderboard_entry != nullptr) {
        temp = head_leaderboard_entry->next_leaderboard_entry;
        delete head_leaderboard_entry;
        head_leaderboard_entry = temp;
    }

}

std::vector<std::string> Leaderboard::splitString(const std::string& mainStr) {
    std::vector<std::string> stringParts;

    std::stringstream string_part_stream;

    for (int i = 0; i < mainStr.length(); i++) {
        if (mainStr[i] != ' ') {
            string_part_stream << mainStr[i];
        } else {
            stringParts.push_back(string_part_stream.str());
            string_part_stream.str("");
        }
    }

    if (!string_part_stream.str().empty()) {
        stringParts.push_back(string_part_stream.str());
    }

    return stringParts;

}