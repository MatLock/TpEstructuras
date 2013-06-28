
#ifndef __RECT_H
#define __RECT_H

#include "Point.h"

#include <vector>
#include <iostream>
#include <utility>

struct Rect {
  Point origin;
  double height;
  double width;
};

typedef std::pair<std::vector<Point>,std::vector<Point> > point_partition;

Rect rect(Point origin, double width, double height);

Point origin(const Rect& r);
double width(const Rect& r);
double height(const Rect& r);

bool contains(const Rect& r, const Point& p);
std::vector<Rect> quadrants(const Rect& r);

point_partition splitInside(const Rect& r, const std::vector<Point>& ps);

std::ostream& operator<<(std::ostream& o, const Rect& r);

#endif

