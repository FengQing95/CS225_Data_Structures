/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
*/


#pragma once
#include "Image.h"
#include "./cs225/PNG.h"
#include "./cs225/HSLAPixel.h"


namespace cs225{
  class StickerSheet{
  public:
    StickerSheet(const Image & picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet & other);
    const StickerSheet & operator=(const StickerSheet & other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image & sticker, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index);
    Image render() const;
    bool translate(unsigned index, unsigned x, unsigned y);
  private:
    unsigned max_;
    Image ** stickers_;
    Image * base_;
    unsigned * x_cor_;
    unsigned * y_cor_;
    void clear_();
    void copy_(const StickerSheet & other);
  };
}
