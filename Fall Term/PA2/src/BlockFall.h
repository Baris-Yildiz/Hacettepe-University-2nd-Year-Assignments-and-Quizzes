#ifndef BLOCKFALL_H
#define BLOCKFALL_H

#define occupiedCellChar "██"
#define unoccupiedCellChar "▒▒"

#include <vector>
#include <string>

#include "Block.h"
#include "LeaderboardEntry.h"
#include "Leaderboard.h"

using namespace std;

class BlockFall {
public:
    /*constructor for the BlockFall class. Initializes the grid, blocks, gravity mode, leaderboard and player name.*/
    BlockFall(string grid_file_name, string blocks_file_name, bool gravity_mode_on, const string &leaderboard_file_name,
              const string &player_name);

    /*destructor for the BlockFall class.*/
    virtual ~BlockFall();

    int rows;   //row number of the grid
    int cols;   //column number of the grid
    vector<vector<int>> grid;   //grid as a vector of vectors of ints.
    vector<vector<bool>> power_up;  //powerup as a vector of bools.
    Block * initial_block = nullptr;    //initial block of the list of blocks.
    Block * active_rotation = nullptr;  //current rotation of the block.
    bool gravity_mode_on = false;   //bool which indicates that the gravity is on.
    unsigned long current_score = 0;    //the current score.
    string leaderboard_file_name;   //file name of the leaderboard
    string player_name; //name of the player
    Leaderboard leaderboard;    //leaderboard used in the current game.

    /*initializes the grid from the given file.*/
    void initialize_grid(const string & input_file);

    /*initializes the blocks from the given file.*/
    void read_blocks(const string & input_file);
private:
    /*creates a new block dynamically*/
    Block * createNewBlock(vector<vector<bool>> shape);

    /*creates the rotations of a block*/
    void createAndAddRotations(Block *block);

    /*appends a block to the linked list of blocks*/
    void appendNewBlock(Block *newBlock);

    /* Creates the right rotation of a block.
     * This function is used in combination with the createAndAddRotations
     * function in order to create every rotation of the block.*/
    Block* createRightRotation(Block* block);

    /*This is a function called only from the destructor to delete every rotation block with
     * all of its rotations.*/
    void deleteAllBlocks();

    /* Deletes every rotation of a block.
     * Called from the deleteAllBlocks() function, whenever a block
     * is going to be deleted.*/
    void deleteAllRotations(Block *block);
};



#endif // BLOCKFALL_H
