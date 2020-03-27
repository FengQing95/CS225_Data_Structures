#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  cur_ = Point(0, 0);
  t_ = NULL;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(! t_->empty()){
    t_->pop();
    isVisited_[cur_.y * image_.width() + cur_.x] = true;

    std::vector<Point> points;
    Point up_ = Point(cur_.x, cur_.y - 1);
    Point down_ = Point(cur_.x, cur_.y + 1);
    Point left_ = Point(cur_.x - 1, cur_.y);
    Point right_ = Point(cur_.x + 1, cur_.y);
    points.push_back(right_);
    points.push_back(down_);
    points.push_back(left_);
    points.push_back(up_);
    while(! t_->empty() && isVisited(Point(t_->peek().x, t_->peek().y))){cur_ = t_->pop();}

    for(unsigned i = 0; i < 4; i++){
      Point tem = points[i];
      if(tem.x < image_.width() && tem.y < image_.height()){
        if(! isVisited(tem) && calculateDelta(image_.getPixel(visited_.x, visited_.y), image_.getPixel(tem.x, tem.y)) <= tolerance_)
        {t_->add(tem);}
      }
    }
    if(! t_->empty()){cur_ = t_->peek();}
  }

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return cur_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool empty1 = t_ ? false : true;
  bool empty2 = other.t_ ? false : true;
  if(! empty1){empty1 = t_->empty();}
  if(! empty2){empty2 = other.t_->empty();}

  return (empty1 && empty2) ? false : true;
}

ImageTraversal::Iterator::Iterator(ImageTraversal * t, Point & start, double & tolerance, PNG & image){
  t_ = t;
  visited_ = start;
  image_ = image;
  cur_ = t_->peek();
  tolerance_ = tolerance;
  isVisited_.resize(image.width() * image.height(), false);
}

bool ImageTraversal::Iterator::isVisited(const Point & point) const{
  return isVisited_[point.x + point.y * image_.width()];
}
