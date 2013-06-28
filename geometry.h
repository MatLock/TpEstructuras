
#ifndef __GEOMETRY_H
#define __GEOMETRY_H

#include "Rect.h"
#include "Circle.h"

#include <algorithm>

namespace geometry {

  class interval {
    public:
      interval(double min, double max): min(min), max(max) {}
      bool overlaps(const interval& i) const {
        return std::max(min, i.min) <= std::min(max, i.max);
      }
    private:    
      double min, max;
  };

  bool overlap(const Rect& r, const Circle& c);
  bool overlap(const Circle& c, const Rect& r);

}

#endif

