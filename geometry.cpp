
#include "Point.h"
#include "geometry.h"

/*
 * Approximate overlap function. Might yield false positives.
 * with low probability. For rectangle r and circle c:
 *   P(r overlaps c|r overlaps square circunscribing c) = pi/4 > 0.78
 */
bool geometry::overlap(const Rect& r, const Circle& c) {
  Point p0 = origin(r);

  interval rw = interval(x(p0), x(p0) + width(r));
  interval rh = interval(y(p0), y(p0) + height(r));
  interval cw = interval(x(center(c)) - radius(c), x(center(c)) + radius(c));
  interval ch = interval(y(center(c)) - radius(c), y(center(c)) + radius(c));
  return rw.overlaps(cw) && rh.overlaps(ch);
}

bool geometry::overlap(const Circle& c, const Rect& r) {
  return overlap(r,c);
}

