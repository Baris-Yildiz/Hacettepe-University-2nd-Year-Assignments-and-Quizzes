#ifndef PA2_GAMECONTROLLER_H
#define PA2_GAMECONTROLLER_H

#include "BlockFall.h"

using namespace std;

class GameController {
public:
    bool play(BlockFall &_game, const string &commands_file); // Function that implements the gameplay
private:
    /*Member that points to the current game object.(A BlockFall object)*/
    BlockFall* game = nullptr;

    int currentI = 0;  // the row where the current block's top left cell is positioned.
    int currentJ = 0;  // the column where the current block's top left cell is positioned.

    Block* currentBlock = nullptr;  //the current block.

    int currentBlockSize = 0;   //size of the current block, used in scoring.

    /*
    * Calculates the current block size.*/
    void calculateBlockSize();


    int highScore = 0;      //current high score.

    /*
     * Prints the current state of the game grid.
     * Takes the argument clear which indicates whether the "before clearing" message
     * will be printed or not. This message should be printed when a row is about to be cleared.
     */
    void printGrid(bool clear);

    /*
     * Prints the current block to the grid.
     * Doesn't embed the block into the grid.
     * */
    vector<vector<int>> printBlock();

    /*
     * Functions that get called by the game commands. E.g. the ROTATE_LEFT command
     * calls the rotateLeft() function.*/
    void rotateRight();
    void rotateLeft();
    void moveRight();
    void moveLeft();
    void dropBlock();
    void switchGravity();

    /* Function that checks if any collision occurs in case
     * block is at row x and column y.
     * */
    bool checkForBlockCollision(Block* block, int x, int y);

    /*Drops the current block.*/
    void drop();

    /*Embeds the current block into the grid.*/
    void saveBlockToGrid();

    /*Advances the current block to the next block on the list.*/
    void createNewBlock();

    /*Scans the grid for rows waiting to be cleared, calls the clearRow() function to clear each one.
     * The print argument signals whether the printGrid(true) function will be called after a clear or not.*/
    void clearRows(bool print);

    /*Clears the row by filling it with zeros. Also calculates the score.*/
    int clearRow(vector<int> &row);

    /*Checks the row for any assembled powerups, returns false if there is none.
     * If there is, clears the row, increases the score accordingly and returns true.*/
    bool checkForPowerup();

    /*Applies gravity to the grid.*/
    void activateGravityOnGrid();

    /*These functions check for endgame conditions.*/
    bool checkIfGameOver();
    bool checkIfGameWin();

    /*Prints the final grid.*/
    void printFinalGrid();

    /*Updates the leaderboard and calls the printFinalGrid() function.*/
    void endGame();

};


#endif //PA2_GAMECONTROLLER_H
