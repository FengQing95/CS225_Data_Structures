#include <iostream>
#include "Image.h"
#include "./cs225/PNG.h"
#include "./cs225/HSLAPixel.h"
using cs225::PNG;

namespace cs225{
  Image::Image(unsigned int width, unsigned int height): PNG(width, height){}
  Image::Image(): PNG(){}

  void Image::lighten(){
    lighten(0.1);
  }

  void Image::lighten(double amount){
    for (unsigned x = 0; x < width(); x++){
      for (unsigned y = 0; y < height(); y++){
        HSLAPixel & pixel = getPixel(x, y);
        pixel.l = pixel.l + amount;
        if (pixel.l > 1.0){pixel.l = 1.0;}
      }
    }
  }

  void Image::darken(){
    darken(0.1);
  }

  void Image::darken(double amount){
    for (unsigned x = 0; x < width(); x++){
      for (unsigned y = 0; y < height(); y++){
        HSLAPixel & pixel = getPixel(x, y);
        pixel.l = pixel.l - amount;
        if (pixel.l < 0.0){pixel.l = 0.0;}
      }
    }
  }

  void Image::saturate(){
    saturate(0.1);
  }

  void Image::saturate(double amount){
    for (unsigned x = 0; x < width(); x++){
      for (unsigned y = 0; y < height(); y++){
        HSLAPixel & pixel = getPixel(x, y);
        pixel.s = pixel.s + amount;
        if (pixel.s > 1.0){pixel.s = 1.0;}
      }
    }
  }

  void Image::desaturate(){
    desaturate(0.1);
  }

  void Image::desaturate(double amount){
    for (unsigned x = 0; x < width(); x++){
      for (unsigned y = 0; y < height(); y++){
        HSLAPixel & pixel = getPixel(x, y);
        pixel.s = pixel.s - amount;
        if (pixel.s < 0.0){pixel.s = 0.0;}
      }
    }
  }

  void Image::grayscale(){
    for (unsigned x = 0; x < width(); x++){
      for (unsigned y = 0; y < height(); y++){
        HSLAPixel & pixel = getPixel(x, y);
        pixel.s = 0.0;
      }
    }
  }

  void Image::rotateColor(double degrees){
    for (unsigned x = 0; x < width(); x++){
      for (unsigned y = 0; y < height(); y++){
        HSLAPixel & pixel = getPixel(x, y);
        pixel.h = pixel.h + degrees;
        if (pixel.h > 360.0){pixel.h = pixel.h - 360.0;}
        if (pixel.h < 0.0){pixel.h = pixel.h + 360.0;}
      }
    }
  }

  void Image::illinify(){
    for (unsigned x = 0; x < width(); x++){
      for (unsigned y = 0; y < height(); y++){
        HSLAPixel & pixel = getPixel(x, y);
        if (pixel.h > 113.5 && pixel.h < 293.5){pixel.h = 216.0;}
        else{pixel.h = 11.0;}
      }
    }
  }

  void Image::scale(double factor){
    unsigned width = this->width();
    unsigned height = this->height();
    PNG * temp = new PNG((unsigned)(width * factor), (unsigned)(height * factor));
    for (unsigned x = 0; x < (unsigned)(width * factor); x++){
      for (unsigned y = 0; y < (unsigned)(height * factor); y++){
        HSLAPixel & pixel_new = temp->getPixel(x, y);
        HSLAPixel & pixel_old = getPixel((unsigned)(x/factor), (unsigned)(y/factor));
        pixel_new = pixel_old;
      }
    }
    resize((unsigned int)(width * factor), (unsigned int)(height * factor));
    for (unsigned x = 0; x < (unsigned)(width * factor); x++){
      for (unsigned y = 0; y < (unsigned)(height * factor); y++){
        HSLAPixel & pixel_new = temp->getPixel(x, y);
        HSLAPixel & pixel_old = getPixel(x, y);
        pixel_old = pixel_new;
      }
    }
    delete temp;
  }

  void Image::scale(unsigned w, unsigned h){
    unsigned width = this->width();
    unsigned height = this->height();
    double factor_w = (double)w / width;
    double factor_h = (double)h / height;
    if (factor_w >= factor_h){scale(factor_h);}
    else{scale(factor_w);}
  }
}
