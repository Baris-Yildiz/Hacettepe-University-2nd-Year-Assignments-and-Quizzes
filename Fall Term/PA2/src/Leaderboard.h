#ifndef PA2_LEADERBOARD_H
#define PA2_LEADERBOARD_H

#include <ctime>
#include <string>
#include "LeaderboardEntry.h"
#include "vector"

#define MAX_LEADERBOARD_SIZE 10

using namespace std;

class Leaderboard {
public:
    LeaderboardEntry* head_leaderboard_entry = nullptr; //the highest score on the leaderboard. / head of the leaderboard linked list.
    int entries = 0; //total entries in the leaderboard.

    /*Reads the leaderboard file and creates the leaderboard linked list.*/
    void read_from_file(const string &filename);

    /*Writes the current state of the leaderboard to the leaderboard file, updating it.*/
    void write_to_file(const string &filename);

    /*Prints the leaderboard to the console.*/
    void print_leaderboard();

    /*Inserts a new entry to the leaderboard linked list.*/
    void insert_new_entry(LeaderboardEntry *new_entry);

    /*Destructor of the Leaderboard class deletes the dynamically allocated leaderboard linked list.*/
    virtual ~Leaderboard();

    /*Splits a string from whitespaces.*/
    std::vector<std::string> splitString(const std::string& mainStr);
};


#endif //PA2_LEADERBOARD_H
