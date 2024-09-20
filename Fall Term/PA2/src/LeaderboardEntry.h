#ifndef PA2_LEADERBOARDENTRY_H
#define PA2_LEADERBOARDENTRY_H

#include <ctime>
#include <string>

using namespace std;

class LeaderboardEntry {
public:
    LeaderboardEntry(unsigned long score, time_t lastPlayed, const string &playerName);

public:
    unsigned long score;
    time_t last_played; //timestamp
    string player_name;
    LeaderboardEntry * next_leaderboard_entry = nullptr;
};

#endif //PA2_LEADERBOARDENTRY_H
