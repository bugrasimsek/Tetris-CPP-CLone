#include "GameController.h"
#include <iostream>
#include <fstream>
#include <string>

bool GameController::play(BlockFall& game, const string& commands_file){
    // TODO: Implement the gameplay here while reading the commands from the input file given as the 3rd command-line
    //       argument. The return value represents if the gameplay was successful or not: false if game over,
    //       true otherwise.

    //game.display_blocks();
    std::ifstream inFile(commands_file); // Opening file in read mode

    if (!inFile)
        return false;

    else{
        std::string line;
        vector<string> lines;

        while (std::getline(inFile, line)) { // Read file line by line
            lines.push_back(line);
        }

        inFile.close(); // Close the file after readings

        //print the lines
        for (int i = 0; i < lines.size(); i++) {
            //TODO: This causes memory error, delete this
            //cout << "\nCommand: " << lines[i] << endl;

            if(game.game_over_block_dont_fit){
                cout << "GAME OVER!" << endl;
                cout << "Next block that couldn't fit: " << endl;
                game.display_single_block(game.active_rotation);
                cout << endl;

                cout << "Final grid and score:\n" << endl;
                cout << "Score: " << game.current_score << endl;
                if(game.current_score > game.leaderboard.highest_score)
                    game.leaderboard.highest_score = game.current_score;

                cout << "High Score: " << game.leaderboard.highest_score << endl;


                for (int i = 0; i < game.rows; i++) {
                    for (int j = 0; j < game.cols; j++) {
                        //cout << grid[i][j] << " ";

                        //if the cell is occupied, print the occupied cell char
                        //grid.at(i).at(j) == 1
                        if(game.grid[i][j] == 0)
                            //cout << occupiedCellChar;
                            cout << unoccupiedCellChar << unoccupiedCellChar;

                        else
                            cout << occupiedCellChar << occupiedCellChar;

                        cout << " ";
                    }
                    cout << "\n";
                }

                cout << endl;

                game.leaderboard.insert_new_entry(new LeaderboardEntry(game.current_score, time(nullptr), game.player_name));

                game.print_leaderboard();

                game.leaderboard.write_to_file(game.leaderboard_file_name);


                return false;
            }

            else if(game.active_rotation == nullptr) {
                /*
                 *
                 */
                cout << "YOU WIN!\nNo more blocks." << endl;

                cout << "Final grid and score:\n" << endl;
                cout << "Score: " << game.current_score << endl;
                if (game.current_score > game.leaderboard.highest_score)
                    game.leaderboard.highest_score = game.current_score;

                cout << "High Score: " << game.leaderboard.highest_score << endl;

                for (int i = 0; i < game.rows; i++) {
                    for (int j = 0; j < game.cols; j++) {
                        //cout << grid[i][j] << " ";

                        //if the cell is occupied, print the occupied cell char
                        //grid.at(i).at(j) == 1
                        if(game.grid[i][j] == 0)
                            //cout << occupiedCellChar;
                            cout << unoccupiedCellChar << unoccupiedCellChar;

                        else
                            cout << occupiedCellChar << occupiedCellChar;

                        cout << " ";
                    }
                    cout << "\n";
                }

                cout << endl;

                game.leaderboard.insert_new_entry(new LeaderboardEntry(game.current_score, time(nullptr), game.player_name));

                game.print_leaderboard();

                game.leaderboard.write_to_file(game.leaderboard_file_name);

                return true;
            }


            // TODO: Check "if possible" to rotate
            else if(lines[i] == "ROTATE_RIGHT")
                game.rotate_active_right();

            else if(lines[i] == "ROTATE_LEFT")
                game.rotate_active_left();
            //TODO: MOVE_RIGHT and MOVE_LEFT

            else if(lines[i] == "MOVE_RIGHT")
                game.move_right();

            else if(lines[i] == "MOVE_LEFT")
                game.move_left();

            else if(lines[i] == "DROP")
                game.drop();

            else if(lines[i] == "PRINT_GRID"){
                game.display_grid();
                cout << endl << endl;
            }


            else if(lines[i] == "GRAVITY_SWITCH"){
                game.gravity_mode_on = !game.gravity_mode_on;

                if(game.gravity_mode_on)
                    game.adjust_grid_to_gravity();
                //cout << "Gravity mode is now: " << (game.gravity_mode_on ? "ON" : "OFF") << endl;
            }



            else{
                cout << "Unknown Command: " << lines[i] << endl;
                continue;
            }
            line.clear();
        }

        //clear the memory
        lines.clear();


        return true;
    };

    return false;
}



