#ifndef PA2_BLOCK_H
#define PA2_BLOCK_H

#include <vector>
#include <iostream>

using namespace std;

class Block {
public:

    vector<vector<bool>> shape; // Two-dimensional vector corresponding to the block's shape
    Block * right_rotation = nullptr; // Pointer to the block's clockwise neighbor block (its right rotation)
    Block * left_rotation = nullptr; // Pointer to the block's counter-clockwise neighbor block (its left rotation)
    Block * next_block = nullptr; // Pointer to the next block to appear in the game
    int x_coord = 0; // X coordinate of the block's top-left corner
    int y_coord = 0; // Y coordinate of the block's top-left corner
    bool isOnGrid = false; // True if the block is on the grid, false otherwise

    // TODO: CHECK ESPECIALLY NOT EQUALS OPERATOR
    bool operator==(const Block& other) const {

        if (this->shape.size() != other.shape.size() || this->shape[0].size() != other.shape[0].size()) {
            return false;
        }

        for (int i = 0; i < this->shape.size(); i++) {
            for (int j = 0; j < this->shape[0].size(); j++) {
                if (this->shape[i][j] != other.shape[i][j]) {

                    return false;
                }
            }
        }

        return true;
    }

    bool operator!=(const Block& other) const {

        if (this->shape.size() != other.shape.size() || this->shape[0].size() != other.shape[0].size()) {
            return true;
        }


        for (int i = 0; i < this->shape.size(); i++) {
            for (int j = 0; j < this->shape[0].size(); j++) {
                if (this->shape[i][j] != other.shape[i][j]) {
                    return true;
                }
            }
        }

        return false;
    }
};


#endif //PA2_BLOCK_H
