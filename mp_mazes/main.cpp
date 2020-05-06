#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;

int main()
{
    // Write your own main here
    SquareMaze myMaze;
    myMaze.makeMaze(100, 100);
    PNG * res = myMaze.drawCreativeMaze();
    res->writeToFile("creative.png");
    delete res;

    return 0;
}
