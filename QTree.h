
#ifndef __QTREE_H
#define __QTREE_H

#include "Point.h"
#include "Circle.h"
#include "Rect.h"
#include "Maybe.h"

#include <vector>

namespace qtree {

 /*
  * If Qtree is a node, you shouldn't access to 'ps'.
  * However if Qtree is a leaf, you shouldn't access to 'nodes'.
  */
  struct QTree {
    bool isNode;
    std :: vector<Point> ps;
    std :: vector<QTree*> nodes;
    Rect rect;
  };
  bool overlaps(QTree* qt, const Circle& c);
  QTree* qleaf(Rect bounds, std::vector<Point> points);
  QTree* qnode(Rect bounds, QTree* q0, QTree* q1, QTree* q2, QTree* q3);
  QTree* create(const Rect& r, const std::vector<Point>& ps, int n);
  maybe::Maybe<Point> nearest(QTree* qt, const Point& p);
  void destroy(QTree* qt);
}

#endif

