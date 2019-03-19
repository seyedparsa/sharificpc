// return pair<point, point> which is intersections point
// for each point if it's not exist, return (INF,INF)
#include<bits/stdc++.h>
#define X first
#define Y second
using namespace std;

typedef long double ld;
typedef pair<ld,ld> point;
typedef pair<point,point> ppp;

point operator + (point A, point B) { return point(A.X+B.X,A.Y+B.Y); }
point operator - (point A, point B) { return point(A.X-B.X,A.Y-B.Y); }
point operator * (double A, point B) { return point(A*B.X,A*B.Y); }
ld dist(point A, point B) { return (A-B).X * (A-B).X + (A-B).Y * (A-B).Y; }
ld dot(point A,point B) { return A.X*B.X + A.Y*B.Y; }

const ld INF = 1e18;
const ld eps = 1e-15;

ppp line_circle_intersection(point p1,point p2,point o,ld r)
{
  point q = dot(o-p1,p2-p1)/dist(p1,p2)*(p2-p1) + p1;
  ld d = r*r - dist(o,q);
  if(d<eps && d>-eps) return ppp(q, point(INF,INF));
  if(d<0) return ppp(point(INF,INF), point(INF,INF));
  point dif = sqrt(d/dist(p1,p2))*(p1-p2);
  return ppp(q-dif,q+dif);
}
