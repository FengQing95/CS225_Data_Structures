/* Your code here! */
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "dsets.h"
#include "cs225/PNG.h"

using std::vector;
using std::string;
using std::queue;
using namespace cs225;

class SquareMaze {
public:
  // SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dir, bool exists);
  vector<int> solveMaze();
  PNG * drawMaze() const;
  PNG * drawMazeWithSolution();
  PNG * drawCreativeMaze();

private:
  int width;
  int height;
  vector<string> walls; // value can be "null", "right", "down" or "both"
  DisjointSets connections;

  int num2x(int num) const;
  int num2y(int num) const;
  int cor2num(int x, int y) const;
};
