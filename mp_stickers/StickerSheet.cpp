#include "StickerSheet.h"
#include "Image.h"
#include "./cs225/PNG.h"
#include "./cs225/HSLAPixel.h"

namespace cs225{
  StickerSheet::StickerSheet(const Image & picture, unsigned max){
    max_ = max;
    stickers_ = new Image * [max];
    for (unsigned i = 0; i < max; i++){
      stickers_[i] = NULL;
    }
    x_cor_ = new unsigned[max];
    y_cor_ = new unsigned[max];
    base_ = new Image(picture);
  }

  StickerSheet::~StickerSheet(){
    clear_();
  }

  StickerSheet::StickerSheet(const StickerSheet & other){
    copy_(other);
  }

  const StickerSheet & StickerSheet::operator=(const StickerSheet & other){
    if (this != &other){
      clear_();
      copy_(other);
    }
    return *this;
  }

  void StickerSheet::clear_(){
    delete base_;
    delete x_cor_;
    delete y_cor_;
    for (unsigned i = 0; i < max_; i++){
      if (stickers_[i]){
        delete stickers_[i];
        stickers_[i] = NULL;
      }
    }
    delete stickers_;
  }

  void StickerSheet::copy_(const StickerSheet & other){
    Image * picture = other.base_;
    unsigned max = other.max_;

    max_ = max;
    stickers_ = new Image * [max];
    for (unsigned i = 0; i < max_; i++){
      stickers_[i] = NULL;
    }
    x_cor_ = new unsigned[max];
    y_cor_ = new unsigned[max];
    base_ = new Image(* picture);

    // copy x_cor_, y_cor_ and stickers_
    for (unsigned i = 0; i < max_; i++){
      x_cor_[i] = other.x_cor_[i];
      y_cor_[i] = other.y_cor_[i];

      if(other.stickers_[i]){stickers_[i] = new Image(* other.stickers_[i]);}
    }
  }

  void StickerSheet::changeMaxStickers(unsigned max){
    StickerSheet * temp = new StickerSheet(*this);
    clear_();

    max_ = max;
    stickers_ = new Image * [max_];
    x_cor_ = new unsigned[max_];
    y_cor_ = new unsigned[max_];
    base_ = new Image(* temp->base_);

    unsigned small = (max_ < temp->max_) ? max_ : temp->max_;


    for (unsigned i = 0; i < max_; i++){
      if(i < small){
        x_cor_[i] = temp->x_cor_[i];
        y_cor_[i] = temp->y_cor_[i];
        if (temp->stickers_[i]){stickers_[i] = new Image(* temp->stickers_[i]);}
        else{stickers_[i] = NULL;}

      }
      else{
        x_cor_[i] = 0;
        y_cor_[i] = 0;
        stickers_[i] = NULL;
      }
    }
    delete temp;
  }

  int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
  for (unsigned i = 0; i < max_; i++){
    if (i == max_){return -1;}
    else{
      if(! stickers_[i]){
        stickers_[i] = new Image(sticker);
        x_cor_[i] = x;
        y_cor_[i] = y;
        return (int)i;
      }
    }
  }
  return -1;
}

  void StickerSheet::removeSticker(unsigned index){
    if (! stickers_[index]){}
    else{
      delete stickers_[index];
      stickers_[index] = NULL;
    }
  }

  Image * StickerSheet::getSticker(unsigned index){
    Image * result = NULL;
    if (stickers_[index]){result = stickers_[index];}
    return result;
  }

  Image StickerSheet::render() const{
    Image result = * base_;
    unsigned w = base_->width();
    unsigned h = base_->height();

    for (unsigned i = 0; i < max_; i++){
      if (! stickers_[i]){}
      else{
        Image temp = Image(* stickers_[i]);
        unsigned new_w = temp.width();
        unsigned new_h = temp.height();
        if (w < new_w + x_cor_[i] || h < new_h + y_cor_[i]){
          w = (w > new_w + x_cor_[i]) ? w : new_w + x_cor_[i];
          h = (h > new_h + y_cor_[i]) ? h : new_h + y_cor_[i];
          result.resize(w, h);
        }
        for (unsigned x = 0; x < temp.width(); x++){
          for (unsigned y = 0; y < temp.height(); y++){
            HSLAPixel & new_pixel = temp.getPixel(x, y);
            if (new_pixel.a > 0.0001){
              HSLAPixel & old_pixel = result.getPixel(x_cor_[i] + x, y_cor_[i] + y);
              old_pixel = new_pixel;
            }
          }
        }

      }
    }
    return result;
  }

  bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if(index >= max_ || (! stickers_[index])){return false;}
    else{
      x_cor_[index] = x;
      y_cor_[index] = y;
      return true;
    }
  }
}
