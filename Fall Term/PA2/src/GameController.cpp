#include <fstream>
#include "GameController.h"
#include "iostream"

bool GameController::play(BlockFall& _game, const string& commands_file){

    game = &_game;
    currentI = 0;
    currentJ = 0;

    if (game->leaderboard.head_leaderboard_entry != nullptr) {
        highScore = game->leaderboard.head_leaderboard_entry->score;
    } else {
        highScore = 0;
    }

    currentBlock = game->initial_block;
    game->active_rotation = currentBlock;

    if (game->gravity_mode_on) {
        activateGravityOnGrid();
        clearRows(false);
    }

    std::ifstream file(commands_file);
    std::string command;


    while(std::getline(file, command)) {

        if (checkIfGameWin()) {
            return true;
        }

        if (checkIfGameOver()) {
            return false;
        }


        if (command == "PRINT_GRID") {
            printGrid(false);
        } else if (command == "MOVE_LEFT") {
            moveLeft();
        } else if (command == "MOVE_RIGHT") {
            moveRight();
        } else if (command == "ROTATE_LEFT") {
            rotateLeft();
        } else if (command == "ROTATE_RIGHT") {
            rotateRight();
        } else if (command == "DROP") {
            dropBlock();
        } else if (command == "GRAVITY_SWITCH") {
            switchGravity();
        } else {
            std::cout << "Unknown command: " << command << "\n";
        }
    }

    std::cout << "GAME FINISHED!\n" << "No more commands.\n" << "Final grid and score:\n\n";
    std::cout << "Score: " << game->current_score << "\nHigh Score: " << highScore << "\n";

    endGame();

    return true;
}

void GameController::printGrid(bool clear) {

    if (game->current_score > highScore) {
        highScore = game->current_score;
    }

    vector<vector<int>> tempGrid;
    if (clear) {
        tempGrid = game->grid;
        std::cout << "Before clearing:\n";
    } else {
        tempGrid = printBlock();
        std::cout << "Score: " << game->current_score << "\n" << "High Score: " << highScore << "\n";
    }

    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->cols; j++) {
            string character = tempGrid[i][j] == 1 ? occupiedCellChar : unoccupiedCellChar;
            std::cout << character;
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}


vector<vector<int>> GameController::printBlock() {
    vector<vector<int>> grid = game->grid;
    vector<vector<bool>> currentBlockShape = currentBlock->shape;

    for (int i = 0; i < currentBlockShape.size(); i++) {
        for (int j = 0; j < currentBlockShape[0].size(); j++) {
            if (currentBlockShape[i][j] == 1) {
                grid[currentI+i][currentJ+j] = currentBlockShape[i][j];
            }
        }
    }

    return grid;
}

void GameController::rotateRight() {

    if (!checkForBlockCollision(currentBlock->right_rotation, currentI, currentJ)) {
        currentBlock = currentBlock->right_rotation;
        game->active_rotation = currentBlock;
    }
}

void GameController::rotateLeft() {
    if (!checkForBlockCollision(currentBlock->left_rotation, currentI, currentJ)) {
        currentBlock = currentBlock->left_rotation;
        game->active_rotation = currentBlock;
    }
}

void GameController::moveRight() {
    if (!checkForBlockCollision(currentBlock, currentI, currentJ+1)) {
        currentJ++;
    }

}


void GameController::moveLeft() {
    if (!checkForBlockCollision(currentBlock, currentI, currentJ-1)) {
        currentJ--;
    }
}


void GameController::dropBlock() {

    drop();
    saveBlockToGrid();

    if (!checkForPowerup()) {
        clearRows(true);
    }

    createNewBlock();

}

void GameController::drop() {
    int distance = 0;

    while(!checkForBlockCollision(currentBlock, currentI+1, currentJ)) {
        if (currentI > game->rows - 1) {
            break;
        }
        currentI++;
        distance++;
    }

    calculateBlockSize();
    game->current_score += currentBlockSize * distance;
}

bool GameController::checkForBlockCollision(Block* block, int i, int j) {
    vector<vector<bool>> blockShape = block->shape;
    int rows = (int)blockShape.size();
    int cols = (int)blockShape[0].size();

    vector<vector<int>> grid = game->grid;

    if (j + cols > grid[0].size() || j < 0) {
        return true;
    }

    if (i + rows > grid.size() || i < 0) {
        return true;
    }

    for (int k = 0; k < rows; k++) {
        for (int l = 0; l < cols; l++) {
            if (grid[k+i][l+j] == 1 && blockShape[k][l] == 1) {
                return true;
            }
        }
    }

    return false;
}

void GameController::switchGravity() {
    game->gravity_mode_on = !(game->gravity_mode_on);
    activateGravityOnGrid();
    clearRows(false);

}

void GameController::saveBlockToGrid() {
    vector<vector<int>> &grid = game->grid;
    vector<vector<bool>> blockShape = currentBlock->shape;

    for (int i = 0; i < blockShape.size(); i++) {
        for (int j = 0; j < blockShape[i].size(); j++) {
            if (blockShape[i][j] == 1) {
                grid[i + currentI][j + currentJ] = 1;
            }
        }
    }

    activateGravityOnGrid();
}

void GameController::createNewBlock() {
    currentBlock = currentBlock->next_block;
    currentI = 0;
    currentJ = 0;
}

void GameController::clearRows(bool print) {
    vector<vector<int>> &grid = game->grid;
    bool full;

    for (int i = 0; i < game->rows; i++) {
        full = true;

        for (int j = 0; j < game->cols; j++) {
            if (grid[i][j] == 0) {
                full = false;
                break;
            }
        }

        if (full) {

            if (print) {
                printGrid(true);
                print = false;
            }

            game->current_score += game->cols;
            if (i != 0) {
                for (int l = i; l > 0; l--) {
                    clearRow(grid[l]);
                    for (int k = 0; k < game->cols; k++) {
                        grid[l][k] = grid[l-1][k];
                    }
                }
            }

            clearRow(grid[0]);

        }
    }
}

int GameController::clearRow(vector<int> &row) {
    int score = 0;
    for (int i = 0; i < game->cols; i++) {
        if (row[i] == 1) {
            score++;
            row[i] = 0;
        }
    }

    return score;
}

bool GameController::checkForPowerup() {
    vector<vector<int>>& grid = game->grid;
    vector<vector<bool>> powerUp = game->power_up;

    int powerUpRows = (int)powerUp.size();
    int powerUpCols = (int)powerUp[0].size();

    for (int i = 0; i < game->rows - powerUpRows + 1; i++) {
        for (int j = 0; j < game->cols - powerUpCols + 1; j++) {
            bool foundPowerUp = true;
            for (int k = 0; (k < powerUpRows) && foundPowerUp; k++) {
                for (int l = 0; l < powerUpCols; l++) {
                    if (grid[i+k][j+l] != powerUp[k][l]) {
                        foundPowerUp = false;
                        break;
                    }
                }
            }

            if (foundPowerUp) {
                printGrid(true);
                game->current_score += 1000;
                for (int m = 0; m < game->rows; m++) {
                    game->current_score += clearRow(grid[m]);
                }
                return true;
            }
        }
    }

    return false;
}

void GameController::calculateBlockSize() {
    currentBlockSize = 0;
    for (int i = 0; i < currentBlock->shape.size(); i++) {
        for (int j = 0; j < currentBlock->shape[0].size(); j++) {
            if (currentBlock->shape[i][j] == 1) {
                currentBlockSize++;
            }
        }
    }
}

void GameController::activateGravityOnGrid() {
    if (game->gravity_mode_on) {
        vector<vector<int>> &grid = game->grid;

        for (int i = game->rows - 2; i > -1; i--) {
            for (int j = 0; j < game->cols; j++) {
                if (grid[i][j] == 1 && grid[i+1][j] == 0) {

                    int new_i = i;
                    grid[i][j] = 0;

                    while (true) {
                        if (new_i >= game->rows-1 || grid[new_i+1][j] == 1) {
                            grid[new_i][j] = 1;
                            break;
                        }
                        new_i++;
                    }

                }
            }
        }
    }
}

bool GameController::checkIfGameOver() {

    if (checkForBlockCollision(currentBlock, 0, 0)) {
        std::cout << "GAME OVER!\n" << "Next block that couldn't fit:\n";

        vector<vector<bool>> blockShape = currentBlock->shape;
        for (int i = 0; i < blockShape.size(); i++) {
            for (int j = 0; j < blockShape[0].size(); j++) {
                std::cout << ((blockShape[i][j] == 1) ? occupiedCellChar : unoccupiedCellChar);
            }
            std::cout << "\n";
        }

        std::cout << "\nFinal grid and score:\n\n";

        std::cout << "Score: " << game->current_score << "\nHigh Score: " << highScore << "\n";
        endGame();

        return true;
    }

    return false;

}

bool GameController::checkIfGameWin() {
    if (currentBlock == nullptr) {
        std::cout << "YOU WIN!\n" << "No more blocks.\n" << "Final grid and score:\n\n";
        std::cout << "Score: " << game->current_score << "\nHigh Score: " << highScore << "\n";

        endGame();
        return true;
    }
    return false;
}

void GameController::printFinalGrid() {

    vector<vector<int>> grid = game->grid;
    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->cols; j++) {
            std::cout << ((grid[i][j] == 1) ? occupiedCellChar : unoccupiedCellChar);
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    game->leaderboard.print_leaderboard();

}

void GameController::endGame() {

    auto* newEntry = new LeaderboardEntry(game->current_score, time(nullptr), game->player_name);
    game->leaderboard.insert_new_entry(newEntry);
    game->leaderboard.write_to_file(game->leaderboard_file_name);

    printFinalGrid();
    std::cout << "\n\n" << std::endl;
}