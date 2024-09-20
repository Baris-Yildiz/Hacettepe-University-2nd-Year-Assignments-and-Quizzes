#include <fstream>
#include "BlockFall.h"

BlockFall::BlockFall(string grid_file_name, string blocks_file_name, bool gravity_mode_on, const string &leaderboard_file_name, const string &player_name) : gravity_mode_on(
        gravity_mode_on), leaderboard_file_name(leaderboard_file_name), player_name(player_name) {
    initialize_grid(grid_file_name);
    read_blocks(blocks_file_name);
    leaderboard.read_from_file(leaderboard_file_name);
}

void BlockFall::read_blocks(const string &input_file) {
    initial_block = new Block();
    Block* head = initial_block;

    std::ifstream file(input_file);

    if (!file.is_open()) {
        std::exit(-1);
    }

    std::string line;
    vector<vector<bool>> blockShape;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            vector<bool> shapeRow;
            for (char i : line) {
                if (i == '1' || i == '0') {
                    shapeRow.push_back(i - 48);
                }
            }
            blockShape.push_back(shapeRow);
        } else {
            if (!blockShape.empty()) {
                Block* newBlock = createNewBlock(blockShape);
                createAndAddRotations(newBlock);
                appendNewBlock(newBlock);
                blockShape.clear();
            }
        }
    }

    if (!blockShape.empty()) {
        power_up = blockShape;
    } else {
        power_up = initial_block->shape;
        delete initial_block;
    }

    initial_block = head->next_block;
    delete head;

    active_rotation = initial_block;
}


void BlockFall::initialize_grid(const string &input_file) {
    std::ifstream file(input_file);

    if (!file.is_open()) {
        std::exit(-1);
    }

    std::string line;
    while (std::getline(file, line)) {
        vector<int> row;
        for (int i = 0; i < line.length(); i+=2) {
            row.push_back(line[i] - 48);
        }
        grid.push_back(row);
    }

    file.close();

    rows = (int)grid.size();
    cols = (int)grid[0].size();
}


BlockFall::~BlockFall() {
    deleteAllBlocks();
}

Block * BlockFall::createNewBlock(vector<vector<bool>> shape) {
    auto* newBlock = new Block();
    newBlock->shape = shape;
    return newBlock;
}

void BlockFall::appendNewBlock(Block *newBlock) {

    Block* curr = initial_block->right_rotation;

    if (curr != nullptr) {
        while (curr != initial_block) {
            curr->next_block = newBlock;
            curr = curr->right_rotation;
        }
    }


    initial_block->next_block = newBlock;
    initial_block = newBlock;
}


void BlockFall::createAndAddRotations(Block* block) {
    vector<vector<bool>> blockShape = block->shape;

    Block* previousRotation = block;
    for (int i = 0; i < 4; i++) {
        Block* rightRotation = createRightRotation(previousRotation);

        if (*rightRotation != *block) {
            previousRotation->right_rotation = rightRotation;
            rightRotation->left_rotation = previousRotation;
            previousRotation = rightRotation;
        } else {

            if (block->right_rotation == nullptr) { //no rotation difference
                block->right_rotation = block->left_rotation = block;
            } else {
                previousRotation->right_rotation = block;
                block->left_rotation = previousRotation;
            }

            delete rightRotation;
            break;
        }
    }
}

Block* BlockFall::createRightRotation(Block *block) {
    vector<vector<bool>> blockShape = block->shape;

    int blockRows = (int)block->shape.size();
    int blockCols = (int)block->shape[0].size();

    auto* rightRotation = new Block();
    vector<vector<bool>> rightRotationShape;


    for (int i = 0; i < blockCols; i++) {
        vector<bool> row;
        row.reserve(blockRows);
        for (int j = blockRows - 1; j > -1; j--) {
            row.push_back(blockShape[j][i]);
        }
        rightRotationShape.push_back(row);
    }

    rightRotation->shape = rightRotationShape;
    return rightRotation;
}

void BlockFall::deleteAllRotations(Block* block) {
    Block* curr = block;
    Block* lastRotation = block->left_rotation;

    while (curr != lastRotation) {
        curr = curr->right_rotation;
        delete curr->left_rotation;
    }

    delete curr;
}

void BlockFall::deleteAllBlocks() {

    if (initial_block == nullptr) {
        return;
    }

    Block* curr = initial_block;
    Block* temp;

    while (curr != nullptr) {
        temp = curr->next_block;
        deleteAllRotations(curr);
        curr = temp;
    }
}