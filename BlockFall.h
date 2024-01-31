#ifndef BLOCKFALL_H
#define BLOCKFALL_H

//#define occupiedCellChar "██"
//#define unoccupiedCellChar "▒▒"

#define occupiedCellChar char(219)
#define unoccupiedCellChar char(177)

#include <vector>
#include <string>

#include "Block.h"
#include "LeaderboardEntry.h"
#include "Leaderboard.h"

using namespace std;

class BlockFall {
public:

    BlockFall(string grid_file_name, string blocks_file_name, bool gravity_mode_on, const string &leaderboard_file_name,
              const string &player_name);
    virtual ~BlockFall();

    int rows;  // Number of rows in the grid
    int cols;  // Number of columns in the grid
    vector<vector<int> > grid;  // 2D game grid
    vector<vector<bool>> power_up; // 2D matrix of the power-up shape
    Block * initial_block = nullptr; // Head of the list of game blocks. Must be filled up and initialized after a call to read_blocks()
    Block * active_rotation = nullptr; // Currently active rotation of the active block. Must start with the initial_block
    bool gravity_mode_on = false; // Gravity mode of the game
    unsigned long current_score = 0; // Current score of the game
    string leaderboard_file_name; // Leaderboard file name, taken from the command-line argument 5 in main
    string player_name; // Player name, taken from the command-line argument 6 in main
    Leaderboard leaderboard;
    bool game_over_block_dont_fit = false; // True if the game is over because the block doesn't fit

    void initialize_grid(const string & input_file); // Initializes the grid using the command-line argument 1 in main
    void read_blocks(const string & input_file); // Reads the input file and calls the read_block() function for each block;
    void create_blocks(vector<string> *matrix);

    void display_blocks();

    void calculate_rotations();

    Block* rotate(Block *block);

    void display_rotations();

    void display_single_block(Block *block);

    Block* rotate_right(Block *block);

    Block *rotate_left(Block *block);

    void display_grid();

    void drop();

    void place_to_start();

    void clear_grid();

    bool does_collide(int row, int col, Block *block);

    void move_right();

    void move_left();

    void rotate_active_right();
    void rotate_active_left();

    void drop_with_gravity();

    void adjust_grid_to_gravity();

    void check_complete_row();

    void check_for_power_up();

    void print_leaderboard();
};



#endif // BLOCKFALL_H
