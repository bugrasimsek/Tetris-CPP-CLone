# Tetris-CPP-Clone

Compile with:

g++ -std=c++11 main.cpp Block.h BlockFall.h BlockFall.cpp GameController.h GameController.cpp LeaderboardEntry.h LeaderboardEntry.cpp Leaderboard.h Leaderboard.cpp -o blockfall

Or, you can use the provided Makefile or CMakeLists.txt within the sample input to compile your
code:

$ make

or

$ mkdir blockfall_build
$ cmake -S . -B blockfall_build/
$ make -C blockfall_build/


After compilation, you can run the program as follows:
$ ./blockfall grid.dat blocks.dat commands.dat GRAVITY_ON leaderboard.txt BlockBuster

<img width="519" alt="Code_UxlajCznj7" src="https://github.com/bugrasimsek/Tetris-CPP-Clone/assets/73181218/04978184-4e50-4a7b-a41a-7809c2a7ec32">
