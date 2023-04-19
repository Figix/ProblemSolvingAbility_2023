#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include "Maze.h"

using namespace std;


int main() {
    
    Maze maze;
    maze.generateMaze();
    maze.generateMine();
    maze.decideA2B();
    maze.solveMaze();
    maze.printSolution();

    return 0;
}