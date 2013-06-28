
#include "Point.h"
#include "Rect.h"
#include "vector"

Rect rect(Point origin, double width, double height) {
  Rect r;
  r.origin = origin;
  r.width = width;
  r.height = height;
  return r;
}

Point origin(const Rect& r) {
  return r.origin;
}

double width(const Rect& r) {
   return r.width;
}

double height(const Rect& r) {
  return r.height;
}

bool contains(const Rect& r, const Point& p) {
  return (((p.x >= r.origin.x) && (p.x < r.origin.x + r.width))
            && ((p.y >= r.origin.y) && (p.y < r.origin.y + r.height)));
}

std::vector<Rect> quadrants(const Rect& r) {
 std::vector<Rect> v;
 Rect a,b,c,d;
 double x = r.width / 2;
 double y = r.height / 2;
 a = rect(r.origin,x,y);
 b = rect(point(r.origin.x,r.origin.y + y),x,y);
 c = rect(point(x,y),x,y);
 d = rect(point(r.origin.x + x,r.origin.y),x,y);
 v.push_back(a);
 v.push_back(b);
 v.push_back(c);
 v.push_back(d);
  return v;
}

point_partition splitInside(const Rect& r, const std::vector<Point>& ps) {
  std::vector<Point> inside;
  std::vector<Point> outside;
  for (int i = 0; i < (int) (ps.size()); i++){
     if (contains(r,ps[i])){
      inside.push_back(ps[i]);
     }else{
       outside.push_back(ps[i]);
     }
  }
  return point_partition(inside, outside);
}

std::ostream& operator<<(std::ostream& o, const Rect& r) {
    Point a,b,c;
    a = point(r.origin.x,r.origin.y + r.height);
    b = point(r.origin.x + r.width, r.origin.y + r.height);
    c = point(r.origin.x + r.width, r.origin.y);
  o << "origin  " << r.origin << a << b << c << std :: endl;
  return o;
}

