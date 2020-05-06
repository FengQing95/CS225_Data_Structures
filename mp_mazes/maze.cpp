/* Your code here! */
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "dsets.h"
#include "cs225/PNG.h"
#include "maze.h"

using std::vector;
using std::string;
using std::queue;
using namespace cs225;

void SquareMaze::makeMaze(int width, int height) {
  // clear if data already exists
  // do not delete walls on the perimeter
  // 2 bits per square: the "down" and "right" walls
  this->width = width;
  this->height = height;
  int total = width * height;
  walls.clear();
  for (int i = 0; i < total; i++) {
    walls.push_back("both");
  }
  connections.clear();
  connections.addelements(total);

  while (connections.size(0) < total) {
    int square = rand() % total;
    int x = num2x(square);
    int y = num2y(square);
    int wall = rand() % 2;
    if (wall == 0) {
      if (x == width - 1 || connections.find(square) == connections.find(cor2num(x+1,y))) {
        continue;
      } else {
        setWall(x, y, 0, false);
        connections.setunion(square, cor2num(x+1,y));
      }
    } else {
      if (y == height - 1 || connections.find(square) == connections.find(cor2num(x,y+1))) {
        continue;
      } else {
        setWall(x, y, 1, false);
        connections.setunion(square, cor2num(x, y+1));
      }
    }
  }
}



bool SquareMaze::canTravel(int x, int y, int dir) const {
  // dir = 0: x += 1
  // dir = 1: y += 1
  // dir = 2: x -= 1
  // dir = 3: y -= 1
  if (x == 0 && dir == 2) {return false;}
  if (x == width - 1 && dir == 0) {return false;}
  if (y == 0 && dir == 3) {return false;}
  if (y == height - 1 && dir == 1) {return false;}

  int square = cor2num(x, y);
  if (dir == 0 && (walls.at(square) == "null" || walls.at(square) == "down")) {
    // move right
    return true;
  }
  if (dir == 1 && (walls.at(square) == "null" || walls.at(square) == "right")) {
    // move down
    return true;
  }
  if (dir == 2 && (walls.at(cor2num(x-1, y)) == "null" || walls.at(cor2num(x-1, y)) == "down")) {
    // move left
    return true;
  }
  if (dir == 3 && (walls.at(cor2num(x, y-1)) == "null" || walls.at(cor2num(x, y-1)) == "right")) {
    // move up
    return true;
  }

  return false;
}


void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  // should be constant time
  // should not prevent cycles from occuring
  // set a wall to be present or not present
  // dir = 0: right; dir = 1: down
  int square = cor2num(x, y);

  if (exists) {
    // create wall
    if (dir == 0 && canTravel(x, y, 0)) {
      // create right wall
      if (walls.at(square) == "null") {
        walls.at(square) = "right";
      } else {
        walls.at(square) = "both";
      }
    }
    if (dir == 1 && canTravel(x, y, 1)) {
      // create down wall
      if (walls.at(square) == "null") {
        walls.at(square) = "down";
      } else {
        walls.at(square) = "both";
      }
    }
  } else {
    // remove wall
    if (dir == 0 && (! canTravel(x, y, 0))) {
      // remove right wall
      if (walls.at(square) == "right") {
        walls.at(square) = "null";
      } else {
        walls.at(square) = "down";
      }
    }
    if (dir == 1 && (! canTravel(x, y, 1))) {
      // remove down wall
      if (walls.at(square) == "down") {
        walls.at(square) = "null";
      } else {
        walls.at(square) = "right";
      }
    }
  }
}


vector<int> SquareMaze::solveMaze() {
  // for each square on the bottom, the distance from the origin is the
  // number of steps of the only path from the origin to that square

  // select the square in the bottom with the largest distance from the origin
  // if there is a tie, use the distination with the smallest x value

  // should be linear time in the number of cells
  vector<int> length(width * height, -1);
  vector<int> steps(width * height, -1);
  vector<int> prevSteps(width * height, -1);
  queue<int> q;
  q.push(0);

  while (! q.empty()) {
    int square = q.front();
    int x = num2x(square);
    int y = num2y(square);

    if (canTravel(x, y, 0) && length[square + 1] < 0) {
      steps[square + 1] = 0;
      length[square + 1] = length[square] + 1;
      q.push(square + 1);
      prevSteps[square + 1] = square;
    }

    if (canTravel(x, y, 1) && length[square + width] < 0) {
      steps[square + width] = 1;
      length[square + width] = length[square] + 1;
      q.push(square + width);
      prevSteps[square + width] = square;
    }

    if (canTravel(x, y, 2) && length[square - 1] < 0) {
      steps[square - 1] = 2;
      length[square- 1] = length[square] + 1;
      q.push(square - 1);
      prevSteps[square - 1] = square;
    }

    if (canTravel(x, y, 3) && length[square - width] < 0) {
      steps[square - width] = 3;
      length[square - width] = length[square] + 1;
      q.push(square - width);
      prevSteps[square - width] = square;
    }

    q.pop();
  }

  int maxVal1 = -1;
  int maxVal2 = maxVal1;
  vector<int> res;

  for (int i = cor2num(0, height - 1); i < width * height; i++) {
    if (maxVal2 < length.at(i)) {
      maxVal1 = i;
      maxVal2 = length[i];
    }
  }

  while(maxVal1 > 0) {
    res.push_back(steps[maxVal1]);
    maxVal1 = prevSteps[maxVal1];
  }

  reverse(res.begin(), res.end());
  return res;
}

PNG * SquareMaze::drawMaze() const {
  // create a new PGN (width*10+1, height*10+1)
  // blacken the topmost and leftmost lines expect (1,0) through (9,0)
  // if right walls exists, blacken ((x+1)*10, y*10+k) for k from 0 to 10
  // if bottom walls exists, blacken (x*10+k,(y+1)*10) for k from 0 to 10

  PNG * res = new PNG (width * 10 + 1, height * 10 + 1);
  for (int i = 0; i < width * 10 + 1; i++) {
    if (i < 1 || i > 9) {
      res->getPixel(i, 0).l = 0;
    }
  }

  for (int i = 0; i < height * 10 + 1;i++) {
    res->getPixel(0, i).l = 0;
  }

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      if (walls.at(cor2num(i, j)) == "right" || walls.at(cor2num(i, j)) == "both") {
        for (int k = 0; k < 11; k++) {
          res->getPixel((i+1)*10, j*10+k).l = 0;
        }
      }

      if (walls.at(cor2num(i, j)) == "down" || walls.at(cor2num(i, j)) == "both") {
        for (int k = 0; k < 11; k++) {
          res->getPixel(i*10+k,(j+1)*10).l = 0;
        }
      }
    }
  }

  return res;
}


PNG * SquareMaze::drawMazeWithSolution() {
  // call drawMaze(), then solveMaze()
  // start at pixel (5,5), then each direction in the vector corresponds to a
  // trail of 11 red (0,1,0.5,1) pixels
  // call the destination corordinates (x,y) and whiten (x*10+k,(y+1)*10) for
  // from 1 to 9

  PNG * res = drawMaze();
  vector<int> steps = solveMaze();

  int x = 5;
  int y = 5;

  for (size_t step = 0; step < steps.size(); step++) {
    if (steps[step] == 0) {
      for (int i = 0; i < 11; i++) {
        res->getPixel(x+i, y).h = 0;
        res->getPixel(x+i, y).s = 1;
        res->getPixel(x+i, y).l = 0.5;
        res->getPixel(x+i, y).a = 1.0;
      }
      x += 10;
    }

    if (steps[step] == 1) {
      for (int i = 0; i < 11; i++) {
        res->getPixel(x, y+i).h = 0;
        res->getPixel(x, y+i).s = 1;
        res->getPixel(x, y+i).l = 0.5;
        res->getPixel(x, y+i).a = 1.0;
      }
      y += 10;
    }

    if (steps[step] == 2) {
      for (int i = 0; i < 11; i++) {
        res->getPixel(x-i, y).h = 0;
        res->getPixel(x-i, y).s = 1;
        res->getPixel(x-i, y).l = 0.5;
        res->getPixel(x-i, y).a = 1.0;
      }
      x -= 10;
    }

    if (steps[step] == 3) {
      for (int i = 0; i < 11; i++) {
        res->getPixel(x, y-i).h = 0;
        res->getPixel(x, y-i).s = 1;
        res->getPixel(x, y-i).l = 0.5;
        res->getPixel(x, y-i).a = 1.0;
      }
      y -= 10;
    }
  }

  int outPoint = x / 10;
  for (int i = 1; i < 10; i++) {
    res->getPixel(outPoint*10+i, height*10).a = 1;
    res->getPixel(outPoint*10+i, height*10).l = 1;
  }

  return res;
}

int SquareMaze::cor2num(int x, int y) const {
  return x + y * width;
}

int SquareMaze::num2x(int num) const {
  return num % width;
}

int SquareMaze::num2y(int num) const {
  return num / width;
}

PNG * SquareMaze::drawCreativeMaze() {
  PNG * res = drawMazeWithSolution();
  int width = res->width();
  int height = res->height();
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      if ((i + j) % 10 == 0) {
        res->getPixel(i, j).h = 196;
        res->getPixel(i, j).l = 0.31;
        res->getPixel(i, j).s = 0.39;
        res->getPixel(i, j).a = 0.92;
      }
    }
  }

  return res;
}
