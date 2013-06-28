
#ifndef __CIRCLE_H
#define __CIRCLE_H

#include "Point.h"
#include <iostream>

struct Circle {
  Point center;
  double radius;
 };

Circle circle(Point center, double radius);

Point center(const Circle& c);
double radius(const Circle& c);

std::ostream& operator<<(std::ostream& o, const Circle& c);

#endif

