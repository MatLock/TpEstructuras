
#include "Circle.h"

#include <iostream>

Circle circle(Point center, double radius) {
  Circle c;
  c.center = center;
  c.radius = radius;
  return c;
}

Point center(const Circle& c) {

  return c.center;
}

double radius(const Circle& c) {

  return c.radius;
}

std::ostream& operator<<(std::ostream& o, const Circle& c) {
  o << "Center:  " << c.center << "Radius:   " << c.radius << std:: endl;
  return o;
}

