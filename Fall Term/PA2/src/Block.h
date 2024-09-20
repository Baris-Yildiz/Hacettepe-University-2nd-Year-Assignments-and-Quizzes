#ifndef PA2_BLOCK_H
#define PA2_BLOCK_H

#include <vector>

using namespace std;

class Block {
public:

    vector<vector<bool>> shape;  /*represents the shape of the block.*/
    Block * right_rotation = nullptr;   /* the right-rotation of the block*/
    Block * left_rotation = nullptr;    /* the left-rotation of the block*/
    Block * next_block = nullptr;   /* the block that needs to be initialized after this block drops.*/

    bool operator==(const Block& other) const { //checks if two blocks have the same shape.

        vector<vector<bool>> otherShape = other.shape;

        if (!otherShape.empty() && !shape.empty()) {
            if (otherShape[0].size() != shape[0].size()) {
                return false;
            }

            if (otherShape.size() != shape.size()) {
                return false;
            }

            for (int i = 0; i < otherShape.size(); i++) {
                for (int j = 0; j < otherShape[i].size(); j++) {
                    if (shape[i][j] != otherShape[i][j]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    bool operator!=(const Block& other) const {  //checks if the blocks do not have the same shape.
        return !(*this == other);
    }
};


#endif //PA2_BLOCK_H
