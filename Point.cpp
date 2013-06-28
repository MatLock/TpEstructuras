
#include "Maybe.h"
#include "Point.h"

#include <algorithm>
#include <cmath>
#include <vector>

Point point(double x, double y) {
  Point p;
  p.x = x;
  p.y = y;
  return p;
}

double x(const Point& p) {

  return p.x;
}

double y(const Point& p) {
  return p.y;
}

bool operator==(const Point& p, const Point& q) {

  return (p.x == q.x) && (p.y == q.y);
}

double dist2(const Point& p, const Point& q) {

  return ((p.x - q.x) * (p.x - q.x)) + ((p.y - q.y) * (p.y - q.y));
}

double dist(const Point& p, const Point& q) {
  return std::sqrt(dist2(p,q));
}

std::ostream& operator<<(std::ostream& o, const Point& p) {
  o << '(' << p.x << ',' << p.y << ')' << std :: endl;
  return o;
}
/* The size of ps > 1
   ps don't contains only the value p */
Point initialiteX(const Point&p,const std::vector<Point>& ps){
       if (not (ps[0] == p)){
           return ps[0];
       }else {
          return ps[1];
       }
}
maybe::Maybe<Point> nearest(const Point& p, const std::vector<Point>& ps){
   if (ps.size() == 0){
      return maybe :: nothing <Point>();
   } else {
      Point m =initialiteX(p,ps);
      double x = dist(p,m);
      for (double i = 0; i < ps.size(); i++){
          if (not (ps[i] == p)){
              if (dist(p,ps[i]) < x ){
               m = ps[i];
              std ::  cout << m << std :: endl;
               x = dist(p,m);
            }
          }
      }
    return maybe :: just(m);
   }
}


