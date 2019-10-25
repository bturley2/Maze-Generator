/*
    BRYCE TURLEY -- Cpts 223 PA3

    Random Maze Generator


 */

#include <string.h>
#include <iostream>
#include "maze.h"


int main(int argc, char * argv[]) {

    if(argc > 1 && !strcmp(argv[1], "--maze")) {
        //execute the 20x20 maze
        std::cout << "============================" << std::endl;
        std::cout << "|| Generating 20x20 maze: ||" << std::endl;
        std::cout << "============================" << std::endl;
        Maze();
        std::cout << "Generation of maze successful. Please see 'maze.svg' file." << std::endl;
    }
    else if (argc > 1 && !strcmp(argv[1], "--bigmaze")) {
        //execute the 50x100 maze
        std::cout << "=============================" << std::endl;
        std::cout << "|| Generating 50x100 maze: ||" << std::endl;
        std::cout << "=============================" << std::endl;
        Maze(true);
        std::cout << "Generation of maze successful. Please see 'bigmaze.svg' file." << std::endl;
    }
    else {
        std::cout << "=============================" << std::endl;
        std::cout << "|| Running in normal mode: ||" << std::endl;
        std::cout << "=============================" << std::endl;
        std::cout << "Normal mode is set to do nothing." << std::endl;
        std::cout << "Please try running 'make maze' or 'make bigmaze' commands." << std::endl;
    }

    return 0;
}