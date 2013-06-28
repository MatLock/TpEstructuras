
#include "Maybe.h"
#include "Point.h"
#include "Rect.h"
#include "QTree.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

inline double rdbl(double min, double max) {
  double d = static_cast<double>(rand())/RAND_MAX;
  return min + d*(max - min);
}

struct gen {
  Rect r;
  gen(Rect r): r(r) {}
  Point operator()() {
    double cx = rdbl(x(origin(r)), x(origin(r)) + width(r));
    double cy = rdbl(y(origin(r)), y(origin(r)) + height(r));
    return point(cx,cy);
  }
};

std::vector<Point> rpoints(int n, const Rect& r) {
  gen g(r);
  std::vector<Point> v(n);
  std::generate_n(v.begin(), n, g);
  return v;
}

struct vanilla_nearest {
  std::vector<Point> ps;
  vanilla_nearest(std::vector<Point> ps): ps(ps) {}
  Point operator()(const Point& p) {
    return fromJust(nearest(p,ps));
  }
};

struct qtree_nearest {
  qtree::QTree* qt;
  qtree_nearest(qtree::QTree* qt): qt(qt) {}
  Point operator()(const Point& p) {
    return fromJust(qtree::nearest(qt,p));
  }
};

void prettyPrint(const std::vector<Point>& ps, std::ostream& o) {
  o << "[";
  std::vector<Point>::const_iterator it = ps.begin();
  for(; it != ps.end(); ++it) {
    o << *it;
    if (it + 1 != ps.end()) o << ", ";
  }
  o << "]";
}

int main2() {
  using namespace maybe;

  clock_t begin;
  double t_vanilla, t_qtree;

  srand(time(0));

  int npoints = 20000;
  Rect r = rect(point(0,0), 100000, 100000);
  std::vector<Point> ps = rpoints(npoints,r);
  std::vector<Point> qs = rpoints(npoints,r);

  std::vector<Point> rs0(npoints);
  begin = clock();
  transform(qs.begin(), qs.end(), rs0.begin(), vanilla_nearest(ps));
  t_vanilla = static_cast<double>(clock()-begin)/CLOCKS_PER_SEC;

  /*
  std::cout << "vanilla: " << std::endl;
  prettyPrint(rs0, std::cout);
  std::cout << std::endl;
  */

  std::vector<Point> rs1(npoints);
  begin = clock();
  qtree::QTree* qt = qtree::create(r, ps, 250);
  transform(qs.begin(), qs.end(), rs1.begin(), qtree_nearest(qt));
  t_qtree = static_cast<double>(clock()-begin)/CLOCKS_PER_SEC;

  //std::cout << *qt << std::endl;

  /*
  std::cout << "qtree: " << std::endl;
  prettyPrint(rs1, std::cout);
  std::cout << std::endl;
  */

  bool eq = true;
  for (unsigned int i = 0; eq && i < qs.size(); i++) {
    Point q = qs[i];
    Point p0 = rs0[i];
    Point p1 = rs1[i];

    std::cout << "Iteration #" << i << std::endl;
    std::cout << "Closest point to " << q <<  " = " << p0
              << ", your algorithm gives: " << p1 << std::endl;

    eq = (p0 == p1) || fabs(dist2(p0,q) - dist2(p1,q)) <= 1e-6;
  }

  std::cout << std::endl;
  assert(eq && "qtree::nearest is computing the wrong results");
  std::cout << "Your qtree implementation seems to be correct... hurray!" << std::endl;

  std::cout << "Time elapsed to compute the nearest point to " << npoints
            << " points (brute force): " << t_vanilla << " secs" << std::endl;

  std::cout << "Time elapsed to compute the nearest point to " << npoints
            << " points (qtree): " << t_qtree << " secs" << std::endl;

  std::cout << std::endl;
  return 0;
}
int main(){
   Point p = point(5,5);
   Point p2 = point(8,8);
   Point p3 = point(2,2);
   Point p4 = point(7,7);
   Point p5 = point(9,9);
   Point p6 = point(12,12);
   Point p7 = point(14,14);
   Point p8 = point(10,10);
   Rect r = rect(point(0,0), 15, 15);
   std::vector<Point> rs1;
   rs1.push_back(p);
   rs1.push_back(p2);
   rs1.push_back(p4);
   rs1.push_back(p5);
   rs1.push_back(p3);
   rs1.push_back(p6);
   rs1.push_back(p7);
   rs1.push_back(p8);
   qtree ::   QTree* qq = qtree :: create(r, rs1,2);
  std ::  cout << qtree :: nearest(qq,p) << std :: endl;


  return 0;
}
int main5(){
    Rect r = rect(point(0,0), 4, 4);
    std::vector<Rect> rs1;
    rs1 = quadrants(r);

    std :: cout << r << std :: endl;
    for(int i = 0; i < 4; i++){
     std :: cout << rs1[i] << std :: endl;
    }

  return 0;
}
