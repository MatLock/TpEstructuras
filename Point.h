
#ifndef __POINT_H
#define __POINT_H

#include "Maybe.h"

#include <iostream>
#include <vector>

struct Point {
   double x;
   double y;
};

Point point(double x, double y);

double x(const Point& p);
double y(const Point& p);

bool operator==(const Point& p, const Point& q);

double dist2(const Point& p, const Point& q);
double dist(const Point& p, const Point& q);

maybe::Maybe<Point> nearest(const Point& p, const std::vector<Point>& ps);
std::ostream& operator<<(std::ostream& o, const Point& p);

#endif

