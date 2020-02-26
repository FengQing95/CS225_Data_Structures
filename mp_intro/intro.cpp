#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <math.h>
#include <string>


void rotate(std::string inputFile, std::string outputFile) {
    // TODO: Part 2
    cs225::PNG input;
    input.readFromFile(inputFile);
    unsigned w = input.width();
    unsigned h = input.height();
    cs225::PNG output(w, h);
    for (unsigned i = 0; i < w; i++){
        for (unsigned j = 0; j < h; j++){
            cs225::HSLAPixel & temp_in = input.getPixel(i, j);
            cs225::HSLAPixel & temp_out = output.getPixel(w - 1 - i, h - 1 - j);
            temp_out = temp_in;
        }
    }
    output.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
    cs225::PNG png(width, height);
    // TODO: Part 3
    for (unsigned i = 0; i < width; i++){
        for (unsigned j = 0; j < height; j++){
            cs225::HSLAPixel & temp = png.getPixel(i, j);
            double x = (double)i;
            double y = (double)j;
            double hue = 0.3 *(x * x + 3 * y * y) / double(width);
            while (hue > 360.0){
                hue = hue - 360.0;
            }
            double sat = sqrt(1 - x / double(width));
            double lum = sqrt(x * y) / double(width);
            double alp = x * (1.0 - y) / double(width * width);
            temp = cs225::HSLAPixel(hue, sat, lum, alp);
        }
    }

    return png;
}
