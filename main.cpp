#include "BlockFall.h"
#include "GameController.h"

#include <string>

int main(int argc, char **argv)
{
    string folder1 = "1_big_grid_gravity_switch";
    string folder2 = "2_game_over";
    string folder3 = "3_gravity_off";
    string folder4 = "4_gravity_on";
    string folder5 = "5_gravity_on";
    string folder6 = "6_gravity_on";
    string folder7 = "7_gravity_on";
    string folder8 = "8_gravity_on";
    string folder9 = "9_gravity_on";
    string folder10 = "10_gravity_on";
    string folder11 = "11_gravity_on";

    string folder = folder1;
    string prefix = "C://Users//bugra//OneDrive - hacettepe.edu.tr//BBM203 Data Structures Lab//Assignment 2 Once Again//";
    string gridFile = prefix + "sampleIO//" + folder + "/grid.dat";
    string blockFile = prefix + "sampleIO//" + folder + "/blocks.dat";
    string commandFile = prefix + "sampleIO//" + folder + "/commands.dat";
    string leaderboardFile = prefix + "sampleIO//leaderboard.txt";
    string playerName = "StackOverthrow";

    // Create a BlockFall instance
    string gravity_mode("GRAVITY_OFF");

    BlockFall game(gridFile, blockFile, (gravity_mode == "GRAVITY_ON"), leaderboardFile, playerName);

    // Create a GameController instance
    GameController controller;

    // Play
    controller.play(game, commandFile);

    return 0;
}