#include "BlockFall.h"
#include <fstream>

#include <iostream>
#include <string>


BlockFall::BlockFall(string grid_file_name, string blocks_file_name, bool gravity_mode_on, const string &leaderboard_file_name, const string &player_name) : gravity_mode_on(
        gravity_mode_on), leaderboard_file_name(leaderboard_file_name), player_name(player_name) {
    initialize_grid(grid_file_name);
    read_blocks(blocks_file_name);
    leaderboard.read_from_file(leaderboard_file_name);
}

//print the leaderboard
void BlockFall::print_leaderboard() {
    leaderboard.print_leaderboard();
}

//rotate active block to the left
void BlockFall:: rotate_active_left(){

    //get the block width and height
    int rotated_width = active_rotation->left_rotation->shape[0].size();
    int rotated_height = active_rotation->left_rotation->shape.size();

    //grid coordinates to be placed are the same as the active block, since the block is rotated around its top left corner
    int x = active_rotation->x_coord;
    int y = active_rotation->y_coord;

    //if the block is out of bounds, don't rotate
    if(x + rotated_width > cols || y + rotated_height > rows)
        return;

    //if the active block is already on the grid, delete it from the grid
    if(active_rotation->isOnGrid){
        //get the block width and height
        int block_width = active_rotation->shape[0].size();
        int block_height = active_rotation->shape.size();

        //grid coordinates to be placed
        int x = active_rotation->x_coord;
        int y = active_rotation->y_coord;

        //delete the block from the grid
        for (int i = 0; i < block_height; i++) {
            for (int j = 0; j < block_width; j++) {
                //if the cell is occupied, delete it
                if(grid[y + i][x + j] == 1)
                    grid[y + i][x + j] = 0;
                //x++;
            }
            //y++;
            //x = 0;
        }
        active_rotation->isOnGrid = false;
    }

    //rotate the active block to the left
    active_rotation = active_rotation->left_rotation;

    //set the x and y coordinates of the active block
    active_rotation->x_coord = x;
    active_rotation->y_coord = y;

    //check collision
    bool collision = does_collide(active_rotation->x_coord, active_rotation->y_coord, active_rotation);

    //if there is collision, rotate the block back to the right
    if(collision)
        active_rotation = active_rotation->right_rotation;
}

//rotate active block to the right
void BlockFall::rotate_active_right() {
    //get the block width and height
    int rotated_width = active_rotation->right_rotation->shape[0].size();
    int rotated_height = active_rotation->right_rotation->shape.size();

    //grid coordinates to be placed are the same as the active block, since the block is rotated around its top left corner
    int x = active_rotation->x_coord;
    int y = active_rotation->y_coord;

    //if the block is out of bounds, don't rotate
    if(x + rotated_width > cols || y + rotated_height > rows)
        return;

    //if the active block is already on the grid, delete it from the grid
    if(active_rotation->isOnGrid){
        //get the block width and height
        int block_width = active_rotation->shape[0].size();
        int block_height = active_rotation->shape.size();

        //grid coordinates to be placed
        int x = active_rotation->x_coord;
        int y = active_rotation->y_coord;

        //delete the block from the grid
        for (int i = 0; i < block_height; i++) {
            for (int j = 0; j < block_width; j++) {
                if(grid[y + i][x + j] == 1)
                    grid[y + i][x + j] = 0;
                //x++;
            }
            //y++;
            //x = 0;
        }
        active_rotation->isOnGrid = false;
    }

    //rotate the active block to the right
    active_rotation = active_rotation->right_rotation;

    //set the x and y coordinates of the active block
    active_rotation->x_coord = x;
    active_rotation->y_coord = y;

    //check collision
    bool collision = does_collide(active_rotation->x_coord, active_rotation->y_coord, active_rotation);

    //if there is collision, rotate the block back to the left
    if(collision)
        active_rotation = active_rotation->left_rotation;

}

//move the active block to the right in grid
void BlockFall::move_right(){
    //check out of bounds
    if(active_rotation->x_coord + active_rotation->shape[0].size() + 1 > cols)
        return;

    //if the active block is already on the grid, delete it from the grid
    if(active_rotation->isOnGrid){
        //get the block width and height
        int block_width = active_rotation->shape[0].size();
        int block_height = active_rotation->shape.size();

        //grid coordinates to be placed
        int x = active_rotation->x_coord;
        int y = active_rotation->y_coord;

        //delete the block from the grid
        for (int i = 0; i < block_height; i++) {
            for (int j = 0; j < block_width; j++) {
                if(grid[y + i][x + j] == 1)
                    grid[y + i][x + j] = 0;
                //x++;
            }
            //y++;
            //x = 0;
        }
        active_rotation->isOnGrid = false;
    }

    //check collision for x =+ 1
    bool collision = does_collide(active_rotation->x_coord + 1, active_rotation->y_coord, active_rotation);

    //if there is collision, don't move
    if(collision)
        return;



    //change the x position of the active block, increment it by 1
    active_rotation->x_coord++;

}

void BlockFall::move_left(){
    //check out of bounds
    if(active_rotation->x_coord -1 < 0)
        return;



    //if the active block is already on the grid, delete it from the grid
    if(active_rotation->isOnGrid){
        //get the block width and height
        int block_width = active_rotation->shape[0].size();
        int block_height = active_rotation->shape.size();

        //grid coordinates to be placed
        int x = active_rotation->x_coord;
        int y = active_rotation->y_coord;

        //delete the block from the grid
        for (int i = 0; i < block_height; i++) {
            for (int j = 0; j < block_width; j++) {
                if(grid[y + i][x + j] == 1)
                    grid[y + i][x + j] = 0;
                //x++;
            }
            //y++;
            //x = 0;
        }
        active_rotation->isOnGrid = false;
    }

    //check collision for x =- 1
    bool collision = does_collide(active_rotation->x_coord - 1, active_rotation->y_coord, active_rotation);

    //if there is collision, don't move
    if(collision)
        return;

    //change the x position of the active block, decrement it by 1
    active_rotation->x_coord--;
}

//drop the active block
void BlockFall::drop() {

    //if the active block is already on the grid, delete it from the grid
    if(active_rotation->isOnGrid){
        //get the block width and height
        int block_width = active_rotation->shape[0].size();
        int block_height = active_rotation->shape.size();

        //grid coordinates to be placed
        int x = active_rotation->x_coord;
        int y = active_rotation->y_coord;

        //delete the block from the grid
        for (int i = 0; i < block_height; i++) {
            for (int j = 0; j < block_width; j++) {
                if(grid[y + i][x + j] == 1)
                    grid[y + i][x + j] = 0;
                //x++;
            }
            //y++;
            //x = 0;
        }
        active_rotation->isOnGrid = false;
    }

    //display the block to be dropped
    //clear_grid();

//    cout << "Dropping block:" << endl;
//    display_single_block(active_rotation);

    //check collision at start
    //place_to_start();
    //delete it from start

    if(gravity_mode_on){
        drop_with_gravity();
        return;
    }

    //drop the block to the grid, as deep as possible

    //start from the bottom
    //get the block width and height
    int block_width = active_rotation->shape[0].size();
    int block_height = active_rotation->shape.size();

    //grid coordinates to be placed
    int x = active_rotation->x_coord;
    //int y = rows - block_height;
    int y = 0;

    //check out of bounds
//    if(y < 0)
//        y = 0;

    if(does_collide(0, 0, active_rotation)){
        game_over_block_dont_fit = true;
        return;
    }

    //check collision before dropping
    //bool collision = does_collide(x, y, active_rotation);

    //increment height until there is no collision
    while (!does_collide(x, y + 1, active_rotation)) {
        //y--; //decrement y, move upwards
        y++;
//
//        //if the block is out of bounds, break
//        if (y < 0)
//            break;

        //if the block is out of bounds, break
        if (y + block_height >= rows){
            break;
        }

    }

    if(y < 0)
        y = 0;

    //set the y_coord of the block
    active_rotation->y_coord = y;

    //drop distance is same as y
    int drop_distance = y;

    //count how many 1's are in the block
    int block_ones = 0;

    for (int i = 0; i < block_height; i++) {
        for (int j = 0; j < block_width; j++) {
            if(active_rotation->shape[i][j] == 1)
                block_ones++;
        }
    }

    //add the drop distance to the score
    current_score += drop_distance * block_ones;

    //place the block to the grid given x and y
    for (int i = 0; i < block_height; i++) {
        for (int j = 0; j < block_width; j++) {
            if (active_rotation->shape[i][j] == 1)
                grid[y + i][x + j] = active_rotation->shape[i][j];
            //x++;
        }
        //y++;
        //x = 0;
    }

    active_rotation->isOnGrid = true;

    //check if power up is activated
    check_for_power_up();

    //check if there are any full rows, if there are, delete them and move the rows above them down
    check_complete_row();

    active_rotation = active_rotation->next_block;

    if(active_rotation == nullptr)
        return;



    if(does_collide(0, 0, active_rotation))
        game_over_block_dont_fit = true;
}


//TODO: THIS DOESN'T WORK WITH SCORING AND POTENTIALLY MORE
void BlockFall::drop_with_gravity(){


    //drop the block to the grid, start from the bottom row of block, drop every block one by one, as deep as possible

    //get the block width and height
    int block_width = active_rotation->shape[0].size();
    int block_height = active_rotation->shape.size();

    //count how many 1's are in the block
    int block_ones = 0;

    for (int i = 0; i < block_height; i++) {
        for (int j = 0; j < block_width; j++) {
            if(active_rotation->shape[i][j] == 1)
                block_ones++;
        }
    }


    int min_drop_distance = 2147483647;


    //loop from the bottom row of the block to the top row
    for(int col = block_height - 1; col >=0; col--){
        for(int row = 0; row < block_width; row++){
            bool collision = false;


            if(active_rotation->shape[col][row] == 0)
                continue;

            else{
                //remove the block from the grid
                grid[col][ row + active_rotation->x_coord] = 0;

                //place the single block to the grid, in the current column, as deep as possible


                for (int k = col; k < rows; k ++) {
                    //if there's a collision, place the block one row above
                    if(grid[k][row + active_rotation->x_coord ] == 1){
                        grid[k - 1][row + active_rotation->x_coord] = 1;

                        if(k - 1 - col < min_drop_distance) //calculate score for left upper corner
                            min_drop_distance = k - 1 - col;
                        collision = true;
                        break;
                    }
                }

                //if there's no collision, place the block to the bottom row
                if(!collision){
                    grid[rows - 1][row + active_rotation->x_coord] = 1;
                    if(rows - 1 - col < min_drop_distance) //calculate score for left upper corner
                        min_drop_distance = rows - 1 - col;
                }

//                grid[rows - 1][row + active_rotation->x_coord] = 1;
//                if(rows - 1 < min_drop_distance) //calculate score for left upper corner
//                    min_drop_distance = rows - 1 - col;
//                continue;


            }
        }
    }

    //set the y_coord of the block
    active_rotation->y_coord = min_drop_distance;





    //add the drop distance to the score
    current_score += min_drop_distance * block_ones;

    //check if power up is activated
    //check_for_power_up();

    //check if there are any full rows, if there are, delete them and move the rows above them down
    check_complete_row();


    active_rotation->isOnGrid = true;

    active_rotation = active_rotation->next_block;

//
//    if(does_collide(0, 0, active_rotation))
//        game_over_block_dont_fit = true;
}

//display grid
void BlockFall::display_grid() {
    //check if the active block will collide with the grid
//    if(does_collide(0, 0, active_rotation)){
//        game_over_block_dont_fit = true;
//        return;
//    }





    //if active block isn't on the grid, write the active block to the grid
    if(!active_rotation->isOnGrid){
        int block_width = active_rotation->shape[0].size();
        int block_height = active_rotation->shape.size();
        int x = active_rotation->x_coord;
        int y = active_rotation->y_coord;
        
        //place the active block to the grid
        for (int i = 0; i < block_height; i++) {
            for (int j = 0; j < block_width; j++) {
                if (active_rotation->shape[i][j] == 1)
                    grid[y + i ][x + j] = active_rotation->shape[i][j];
                //x++;
            }
            //y++;
            //x = 0;
        }
        active_rotation->isOnGrid = true;
    }

    cout << "Score: " << current_score << endl;
    if(current_score > leaderboard.highest_score)
        leaderboard.highest_score = current_score;

    cout << "High Score: " << leaderboard.highest_score << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            //cout << grid[i][j] << " ";

            //if the cell is occupied, print the occupied cell char
            //grid.at(i).at(j) == 1
            if(grid[i][j] == 0)
                cout << unoccupiedCellChar << unoccupiedCellChar;

            else
                cout << occupiedCellChar << occupiedCellChar;

            cout << " ";
        }
        cout << "\n";
    }
}

//check collision
bool BlockFall::does_collide(int x_coord, int y_coord, Block *block) {
    //get the block width and height

    int block_width = block->shape[0].size();
    int block_height = block->shape.size();

    //check if there is a collision

    for (int i = 0; i < block_height; i++) {
        for (int j = 0; j < block_width; j++) {
            if(block->shape[i][j] == 0)
                continue;

            //if cell has a block and the grid cell is occupied, there's collision
            else{
//                display_single_block(block);
//                display_grid();
//                cout << "x: " << x_coord << " y: " << y_coord << endl;
//                cout << "x_coord + i: " << x_coord + i << " y_coord + j: " << y_coord + j << endl;
//                cout << "grid[x_coord + i][y_coord + j]: " << grid[x_coord + i][y_coord + j] << endl;
                if (grid[y_coord + i][x_coord + j] == 1)
                    return true;
            }

        }
    }

    return false;
}


//create a linked list of blocks from the vector of strings
void BlockFall::create_blocks(vector<string> *matrix) {
    //TODO: dynamic allocation?
    //get the size of the matrix
    int rows = matrix->size();

    //create a 2D vector of bools
    vector<vector<bool>> shape;

    //travel the matrix
    for (int i = 0; i < rows; i++) {
        bool blockFinished = false;

        //get the string
        string curLine = (*matrix)[i];

        //create a vector of bools, will be recreated at each iteration
        vector<bool> row;

        //add the content of the string to the vector of bools (row)
        for (int j = 0; j < curLine.length(); j++) {
            if(curLine[j] == '0')
                row.push_back(false);

            else if(curLine[j] == '1')
                row.push_back(true);

            if(curLine[j] == ']')
                blockFinished = true;
        }

        //add the row to the shape
        shape.push_back(row);

        //if a "]" is encountered, the block is finished
        if(blockFinished){
            //create a block
            Block *block = new Block();

            //set the block shape
            block->shape = shape;

            //set the next block
            block->next_block = nullptr;

            //if the initial block is null, set the initial block
            if(initial_block == nullptr){
                initial_block = block;
            }

            //else, set the next block of the last block
            else{
                Block *last_block = initial_block;
                while (last_block->next_block != nullptr) {
                    last_block = last_block->next_block;
                }
                last_block->next_block = block;
            }

            //clear the shape
            shape.clear();

            //clear the row
            row.clear();

            //continue to the next iteration
            continue;
        }

    }

}


//rotate right one block
Block* BlockFall::rotate_right(Block *block) {
    //rotate the block to the right
    Block *right_rotation = new Block();

    int rows = block->shape.size();
    int cols = block->shape[0].size();

    // Create a new matrix with rotated dimensions
    vector<vector<bool>> rotated(cols, vector<bool>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotated[j][rows - 1 - i] = block->shape[i][j];
        }
    }

    right_rotation->shape = rotated;
    //!right_rotation-> left_rotation = block;
    right_rotation -> next_block = block -> next_block; //!do here?
    return right_rotation;
}

//rotate left one block
Block* BlockFall::rotate_left(Block *block) {
    //rotate the block to the right
    Block *left_rotation = new Block();

    int rows = block->shape.size();
    int cols = block->shape[0].size();

    // Create a new matrix with rotated dimensions
    vector<vector<bool>> rotated(cols, vector<bool>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = cols - 1; j >= 0; --j) {
            rotated[cols - 1 - j][i] = block->shape[i][j];
        }
    }

    left_rotation->shape = rotated;
    //!left_rotation-> right_rotation = block;
    left_rotation -> next_block = block -> next_block; //!do here?
    return left_rotation;
}

//calculate right and left rotations for a block, add them to a circular linked list for the block
void BlockFall::calculate_rotations() {
    Block *cur = initial_block;
    while (cur != nullptr) {
        Block *right = rotate_right(cur);
        Block *left = rotate_left(cur);

        //if the right rotation is the same as the original block, delete it
        if (right->shape == cur->shape) {
            delete right;
            delete left;
            cur->right_rotation = cur;
            cur-> left_rotation = cur;
        }

        //else, check if right and left rotations are same
        else if (right->shape == left->shape) {
            delete left;
            right -> right_rotation = cur;
            right -> left_rotation = cur;
            cur->right_rotation = right;
            cur->left_rotation = right;
        }

        //else, set the right and left rotations
        else {
            cur -> right_rotation = right;
            right -> left_rotation = cur;

            cur -> left_rotation = left;
            left -> right_rotation = cur;

            Block * doubleRight = rotate_right(right);
            right -> right_rotation = doubleRight;
            doubleRight -> left_rotation = right;

            left -> left_rotation = doubleRight;
            doubleRight -> right_rotation = left;
        }

        cur = cur->next_block;
    }
}

void BlockFall::read_blocks(const string &input_file) {
    // TODO: initilizze the "active_rotation"
    // TODO: For every block, generate its rotations...

    //string matrix
    vector<string> matrix;

    std::ifstream inFile(input_file); // Opening file in read mode
    if (!inFile)
        return;

    else{
        std::string line;
        while (std::getline(inFile, line)) { // Read file line by line
            //std::cout << line << std::endl;
            //std::cout << "line length: " << line.length() << std::endl;

            //empty lines are skipped, not added to the matrix
            if(line == "")
                continue;

            matrix.push_back(line);


        }
        inFile.close(); // Close the file after readings
    };

    create_blocks(&matrix);
    matrix.clear();

    //delete the last block from the linked list, set it as the power up
    Block *last_block = initial_block;
    Block *prev_block = nullptr;
    while (last_block->next_block != nullptr) {
        prev_block = last_block;
        last_block = last_block->next_block;
    }
    power_up = last_block->shape;
    prev_block->next_block = nullptr;
    delete last_block;

    calculate_rotations();

    active_rotation = initial_block;
    //display_blocks();
    //display_rotations();

}

void BlockFall::initialize_grid(const string &input_file) {
//    int rows = 0;
//    int cols = 0;

    vector<vector<int>> matrix;
    std::ifstream inFile(input_file); // Opening file in read mode

    if (!inFile)
        return;

    else{
        std::string line;
        vector<string> lines;
        while (std::getline(inFile, line)) { // Read file line by line
            //rows++;
            lines.push_back(line);

            vector<int> row;
            for (int i = 0; i < line.length(); i ++) {
                if(line[i] == ' ' || line[i] == '\n')
                    continue;

                //convert char to int and push to row
                int num = line[i] - '0';
                row.push_back(num);
            }
            matrix.push_back(row);
        }

        //cols = line.length();
        inFile.close(); // Close the file after readings
    };

    //set rows and cols
//    this->rows = rows;
//    this->cols = cols;

    this -> rows = matrix.size();
    this -> cols = matrix[0].size();

    //set grid
    this->grid = matrix;

}

BlockFall::~BlockFall() {
    // TODO: Free dynamically allocated memory used for storing game blocks

    Block *cur = initial_block;
    while (cur != nullptr) {
        Block *next = cur->next_block;
        Block * right = cur->right_rotation;
        while (right != cur) {
            Block *temp = right->right_rotation;

            //clear the shape
            for (int i = 0; i < right->shape.size(); i++) {
                right->shape[i].clear();
            }
            right->shape.clear();

            delete right;
            right = temp;
        }
        delete right;

        cur = next;
    }
    initial_block = nullptr;
    active_rotation = nullptr;

    //delete power up
    for (int i = 0; i < power_up.size(); i++) {
        power_up[i].clear();
    }
    power_up.clear();

    //delete grid
    for (int i = 0; i < grid.size(); i++) {
        grid[i].clear();
    }
    grid.clear();

    //clear rows and cols
//    rows = 0;
//    cols = 0;

}

//TODO: Currently unused
//clear the grid
void BlockFall::clear_grid() {
    //make all cells unoccupied
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols ; j++) {
            grid[i][j] = 0;
        }
    }
}

//place the active block to the grid
void BlockFall::place_to_start() {
    //grid coordinates to be placed
    int x = 0;
    int y = 0;

    //get the block width and height
    int block_width = active_rotation->shape[0].size();
    int block_height = active_rotation->shape.size();

    //place the block to the grid so that first cell of block overlaps with the first cell of the grid
    for (int i = 0; i < block_height; i++) {
        for (int j = 0; j < block_width; j++) {
            grid[y + i][x + j] = 0;
            //x++;
        }
        //y++;
        //x = 0;
    }


}

Block* BlockFall::rotate(Block *block) {
    //rotate the block to the right
    Block *right_rotation = new Block();

    int rows = block->shape.size();
    int cols = block->shape[0].size();

    // Create a new matrix with rotated dimensions
    vector<vector<bool>> rotated(cols, vector<bool>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotated[j][rows - 1 - i] = block->shape[i][j];
        }
    }

    right_rotation->shape = rotated;
    //!right_rotation-> left_rotation = block;
    right_rotation -> next_block = block -> next_block; //!do here?
    return right_rotation;
}


//TODO: delete these functions when you're done
//displays the linked list of blocks, used for debugging
void BlockFall::display_blocks() {
    int counter = 0;
    Block *block = initial_block;
    while (block != nullptr) {
        cout << "block -  " << counter << endl;
        display_single_block(block);
        block = block->next_block;
        counter++;
    }

    //also display the power up
    cout << "\npower up: " << endl;
    for (int i = 0; i < power_up.size(); i++) {
        for (int j = 0; j < power_up[0].size() ; j++) {
            cout << power_up[i][j] << " ";
        }
        cout << endl;
    }
}

//display the rotations of a block, used for debugging
void BlockFall:: display_rotations() {
    Block *cur = initial_block;
    while (cur != nullptr) {
        cout << "original: " << endl;
        display_single_block(cur);

        Block * right = cur->right_rotation;
        while (right != cur) {
            cout << "right rotation: " << endl;
            display_single_block(right);

            right = right->right_rotation;
        }
        cout << "back to original: " << endl;
        display_single_block(right);

        cur = cur->next_block;
    }


}

void BlockFall::display_single_block(Block* block) {
    for (int i = 0; i < block->shape.size(); i++) {
        for (int j = 0; j < block->shape[0].size() ; j++) {
            if(block->shape[i][j] == 1)
                //cout << occupiedCellChar;
                cout << occupiedCellChar << occupiedCellChar << " ";

            else
                //cout << unoccupiedCellChar;
                cout << unoccupiedCellChar << unoccupiedCellChar << " ";
        }
        cout << endl;
    }
}

//make the flying blocks fall down
void BlockFall::adjust_grid_to_gravity() {

    //1. if the active block is on the grid, delete it from the grid for now
    if(active_rotation->isOnGrid){
        //get the block width and height
        int block_width = active_rotation->shape[0].size();
        int block_height = active_rotation->shape.size();

        //grid coordinates to be placed
        int x = active_rotation->x_coord;
        int y = active_rotation->y_coord;

        //delete the block from the grid
        for (int i = 0; i < block_height; i++) {
            for (int j = 0; j < block_width; j++) {
                if(grid[y + i][x + j] == 1)
                    grid[y + i][x + j] = 0;
                //x++;
            }
            //y++;
            //x = 0;
        }
    }

    //2. check the grid from bottom to top, if there's a 1, check if there's a 0 below it
    //(actually check from second to last row to the top)
    //(active block is not on the grid, so it's not checked)
    for(int i = rows - 2; i >= 0; i--){
        for(int j = 0; j < cols; j++){
            //if there's a 1, check if there's a 0 below it
            if(grid[i][j] == 1){
                //if there's a 0 below it, move the 1 down as much as possible
                if(grid[i + 1][j] == 0){
                    //move the 1 down as much as possible
                    int k = i + 1;
                    while (grid[k][j] == 0) {
                        k++;
                        //if the block is out of bounds, break
                        if (k >= rows)
                            break;
                    }
                    //place the 1 to the grid
                    grid[k - 1][j] = 1;
                    grid[i][j] = 0;
                }
            }
        }
    }

    //5. add the active block to the grid if it should be on the grid
    if(active_rotation->isOnGrid){
        //get the block width and height
        int block_width = active_rotation->shape[0].size();
        int block_height = active_rotation->shape.size();
        int x = active_rotation->x_coord;
        int y = active_rotation->y_coord;

        //place the active block to the grid
        for (int i = 0; i < block_height; i++) {
            for (int j = 0; j < block_width; j++) {
                if (active_rotation->shape[i][j] == 1)
                    grid[y + i ][x + j] = active_rotation->shape[i][j];
                //x++;
            }
            //y++;
            //x = 0;
        }
        active_rotation->isOnGrid = true;
    }
}

//check if there are any full rows, if there are, delete them and move the rows above them down
void BlockFall::check_complete_row() {

    //active block is not on the grid, so it's not checked

    //check the grid from bottom to top
    for(int i = rows - 1; i >= 0; i--){
        bool full = true;
        for(int j = 0; j < cols; j++){
            //if there's a 0, break, the row is not full
            if(grid[i][j] == 0){
                full = false;
                break;
            }
        }

        //if the row is full, delete it and move the rows above it down
        if(full){
            cout << "Before Clearing: "<< endl;
            //delete active block from the grid
            if(active_rotation->isOnGrid){
                //get the block width and height
                int block_width = active_rotation->shape[0].size();
                int block_height = active_rotation->shape.size();

                //grid coordinates to be placed
                int x = active_rotation->x_coord;
                int y = active_rotation->y_coord;

                //delete the block from the grid
                for (int i = 0; i < block_height; i++) {
                    for (int j = 0; j < block_width; j++) {
                        if(grid[y + i][x + j] == 1)
                            grid[y + i][x + j] = 0;
                        //x++;
                    }
                    //y++;
                    //x = 0;
                }
                active_rotation->isOnGrid = false;
            }

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    //cout << grid[i][j] << " ";

                    //if the cell is occupied, print the occupied cell char
                    //grid.at(i).at(j) == 1
                    if(grid[i][j] == 0)
                        cout << unoccupiedCellChar << unoccupiedCellChar;

                    else
                        cout << occupiedCellChar << occupiedCellChar;

                    cout << " ";
                }
                cout << "\n";
            }

            //delete the row
            for(int j = 0; j < cols; j++){
                grid[i][j] = 0;
            }

            //move the rows above it down
            for(int k = i - 1; k >= 0; k--){
                for(int j = 0; j < cols; j++){
                    grid[k + 1][j] = grid[k][j];
                }
            }

            //increment the score
            current_score += cols;
        }
    }
}

//check for power up in grid
void BlockFall::check_for_power_up() {

    //display_grid();

    //check the all grid, find the power up shape
    int power_up_width = power_up[0].size();
    int power_up_height = power_up.size();

    for(int i = 0; i < rows - power_up_height; i++){
        for(int j = 0; j < cols - power_up_width; j++){
            bool found = true;


            for(int k = 0; k < power_up_height; k++){
                for(int l = 0; l < power_up_width; l++){
                    if(grid[i + k][j + l] != power_up[k][l]){
                        found = false;
                        break;
                    }
                }
                if(!found)
                    break;
            }

            //if the power up is found, clear the grid
            if(found){
                //cout << "found" << endl;
                //add 1 point for each occupied cell on the grid that is being cleared
                for(int k = 0; k < rows; k++){
                    for(int l = 0; l < cols; l++){
                        if(grid[k][l] == 1)
                            current_score++;
                    }
                }


                //clear the grid
                for(int k = 0; k < rows; k++){
                    for(int l = 0; l < cols; l++){
                        grid[k][l] = 0;
                    }
                }

                //increment the score
                current_score += 1000;


            }
        }
    }

    // if power up detected the grid is instantly cleared,
    // awarding 1000 bonus points plus an additional point for each occupied cell on the grid that is being cleared
}