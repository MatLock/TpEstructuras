
#include "QTree.h"
#include "Maybe.h"
#include "geometry.h"
#include "Rect.h"
#include "Point.h"

#include <limits>
#include <iomanip>
#include <iostream>

namespace qtree {

  using namespace maybe;

  QTree* qleaf(Rect bounds, std::vector<Point> points) {
    QTree* qt = new QTree;
    qt -> ps = points;
    qt -> rect = bounds;
    qt -> isNode = false;
    return qt;
  }

  QTree* qnode(Rect bounds, QTree* q0, QTree* q1, QTree* q2, QTree* q3) {
    std :: cout << "node created" << std :: endl;
    QTree* qt = new QTree;
    qt -> isNode = true;
    qt -> rect = bounds;
    qt -> nodes.push_back(q0);
    qt -> nodes.push_back(q1);
    qt -> nodes.push_back(q2);
    qt -> nodes.push_back(q3);
    return qt;
  }

  QTree* create(const Rect& r, const std::vector<Point>& ps, int n) {
    QTree* qt;
      if ((int) (ps.size()) <= n){
         qt = qleaf(r,ps);
        std :: cout << "leaf created" << std :: endl;
     }else {
         QTree *qt0,*qt1,*qt2,*qt3;
         std :: vector<Rect>rects = quadrants(r);
         point_partition a,b,c;
         a = splitInside(rects[0],ps);
         b = splitInside(rects[1],a.second);
         c = splitInside(rects[2],b.second);

         qt0 = create(rects[0], a.first,n);
         qt1 = create(rects[1], b.first,n);
         qt2 = create(rects[2], c.first,n);
         qt3 = create(rects[3], c.second,n);

         qt = qnode(r,qt0,qt1,qt2,qt3);
    }
    return qt;
  }

  bool overlaps(QTree* qt, const Circle& c) {

     return geometry :: overlap(qt ->rect,c);
  }

  double shrinkRadius(const Point& p, const Maybe<Point>& q, double r) {
    if (isNothing(q)){
       return r;
    }
    double x = dist(p,fromJust(q));
    return std :: min(r,x);
  }

  void addIfJust(std::vector<Point>& ps, const Maybe<Point>& q) {
    if (isJust(q)){
      ps.push_back(fromJust(q));
    }
  }

  Maybe<Point> qtNearest(QTree* qt, const Point& p, double r) {

    std::vector<Point> vs;
    Maybe<Point> r0,r1,r2,r3;
    double distMin = r;
    Circle c = circle(p,distMin);

     /* base case */
    if (not (qt ->isNode)){
       if (qt ->ps.empty()){
          return maybe :: nothing<Point>();
       }else {
        return nearest(p,qt-> ps);
       }
    }

     /* recursive case */
     if (overlaps(qt ->nodes[0],c)){
        r0 = qtNearest(qt ->nodes[0],p,distMin);
        distMin = shrinkRadius(p,r0,distMin);
        c = circle(p,distMin);
        addIfJust(vs,r0);
     }
     if (overlaps(qt ->nodes[1],c)){
        r1 = qtNearest(qt ->nodes[1],p,distMin);
        distMin = shrinkRadius(p,r1,distMin);
        c = circle(p,distMin);
        addIfJust(vs,r1);
     }
     if (overlaps(qt ->nodes[2],c)){
        r2 = qtNearest(qt ->nodes[2],p,distMin);
        distMin = shrinkRadius(p,r2,distMin);
        c = circle(p,distMin);
        addIfJust(vs,r2);
     }
     if (overlaps(qt ->nodes[3],c)){
        r3 = qtNearest(qt ->nodes[3],p,distMin);
        addIfJust(vs,r3);
     }

   Maybe<Point>result = nearest(p,vs);
   return result;
  }

  Maybe<Point> nearest(QTree* qt, const Point& p) {
    return qtNearest(qt, p, std::numeric_limits<double>::max());
   }

  std::ostream& prettyPrint(std::ostream& o, QTree* qt, int indent) {
    // Implementar
    return o;
  }

  std::ostream& operator<<(std::ostream& o, QTree* qt) {
    return prettyPrint(o, qt, 0);
  }

  void destroy(QTree* qt) {
    // Implementar (OPCIONAL)
  }
}

