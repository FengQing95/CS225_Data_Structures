#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
using namespace cs225;

int main() {
  Image base; base.readFromFile("base.png");
  Image s1;    s1.readFromFile("sticker1.png");
  //s1.scale(0.3);
  Image s2;    s2.readFromFile("sticker2.png");
  s2.scale(0.7);

  StickerSheet sheet(base, 2);
  sheet.addSticker(s1, 10, 400);
  sheet.addSticker(s2, 500, 400);

  sheet.render().writeToFile("myImage.png");
}
