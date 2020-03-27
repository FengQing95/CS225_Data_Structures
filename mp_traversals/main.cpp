
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG test;
  test.readFromFile("tests/i.png");
  HSLAPixel c(270, 0.8, 0.5);
  MyColorPicker newColor(c);

  DFS fill1(test, Point(0, 0), 0.2);
  BFS fill2(test, Point(10, 10), 0.1);

  FloodFilledImage filledImage(test);
  filledImage.addFloodFill(fill1, newColor);
  filledImage.addFloodFill(fill2, newColor);

  Animation animation = filledImage.animate(200);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");



  return 0;
}
