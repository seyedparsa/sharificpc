#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef ld cord;
typedef complex<ld> PT;
#define X real()
#define Y imag()
#define F first
#define S second
#define pb push_back
#define sz(x) ((int)(x).size())

const ld EPS = 1e-12;

const int ON = 0, LEFT = 1, RIGHT = -1, BACK = -2, FRONT = 2, IN = 3, OUT = -3;

inline bool Geq(ld a, ld b){ return a - b > -EPS; }
inline bool Grt(ld a, ld b){ return a - b > EPS; }
inline bool Leq(ld a, ld b){ return a - b < EPS; }
inline bool Lss(ld a, ld b){ return a - b < -EPS; }
inline bool Equ(ld a, ld b){ return abs(a-b) < EPS; }

struct pt{
	cord x, y;
	pt(cord x, cord y): x(x), y(y) {}
	pt(){}
	pt operator + (pt r){
		return pt(x+r.x, y+r.y);
	}
	pt operator - (pt r){
		return pt(x-r.x, y-r.y);
	}
	pt operator * (cord c) const{
		return pt(x*c, y*c);
	}
	pt operator / (cord c) const{
		return pt(x/c, y/c);
	}
	bool operator < (const pt r) const{
		return (x < r.x || x == r.x && y < r.y);
	}
	cord operator ^ (pt r){
		return x*r.y - y*r.x;
	}
	cord operator * (pt r){
		return x*r.x + y*r.y;
	}
};

bool byX(const pt &a, const pt &b){
	if (Equ(a.x, b.x)) return Lss(a.y, b.y);
	return Lss(a.x, b.x);
}
bool byY(const pt &a, const pt &b){
	if (Equ(a.y, b.y)) return Lss(a.x, b.x);
	return Lss(a.y, b.y);
}
struct cmpXY{ bool operator ()(const pt &a, const pt &b){ return byX(a, b); } };
struct cmpYX{ bool operator ()(const pt &a, const pt &b){ return byY(a, b); } };

istream& operator >> (istream &in, pt &p){ in >> p.x >> p.y; return in; }
ostream& operator << (ostream &out, pt p){ out << p.x << ' ' << p.y; return out; }
pt operator * (cord c, pt p){ return p*c; }
cord norm(pt a){ return a*a; }
ld abs(pt a){ return sqrt(norm(a)); }
pt unit(pt a){ return a/abs(a); } 
pt rot(pt a){ return pt(-a.y, a.x); }
ld dis(pt a, pt b){ return abs(a-b); }
int sgn(ld x){ return (x < -EPS ? -1 : x > EPS ? 1 : 0); }
int dir(pt a, pt b, pt c){ return sgn((b-a)^(c-a)); }

pt proj(pt a, pt b, pt c){
	b = b-a, c = c-a;
	return a + (b*c)/(b*b)*b;
}

pt reflect(pt a, pt b, pt c){
	pt d = c;
	b = b-a, c = c-a;
	return d + (c^b)/abs(b)*rot(unit(b))*2;
}

bool intersect(pt a, pt b, pt c, pt d){
	int as = dir(c, d, a), bs = dir(c, d, b),
		cs = dir(a, b, c), ds = dir(a, b, d);
	if (as && as == bs || cs && cs == ds)
		return false;
	else if (as || bs || cs || ds)
		return true;
	for (int j = 0; j < 2; j++){
		cord mX = min(a.x, b.x), MX = max(a.x, b.x),
			 mY = min(a.y, b.y), MY = max(a.y, b.y);
		for (int k = 0; k < 2; k++){
			if (c.x + EPS > mX && c.x < MX + EPS && c.y + EPS > mY && c.y < MY + EPS)
				return true;
			swap(c, d);
		}
		swap(a, c); swap(b, d);
	}
	return false;
}

pt intersection(pt a, pt b, pt c, pt d){
	cord c1 = (b-a)^(c-a), c2 = (b-a)^(d-a);
	return (c1*d - c2*c)/(c1 - c2);
}

ld signedArea(vector<pt> &p){
	int n = p.size();
	cord res = 0;
	for (int i = 0; i < n; i++)
		res += (p[i]^p[(i+1)%n]);
	return (ld)res/2;
}

ld area(vector<pt> &poly){
	return abs(signedArea(poly));
}

//relative position of c toward ab
int relpos(pt a, pt b, pt c){
	b = b-a; c = c-a;
	if (Grt(b^c, 0)) return LEFT;
	if (Lss(b^c, 0)) return RIGHT;
	if (Lss(b*c, 0)) return BACK;
	if (Grt(b*c, abs(b))) return FRONT;
	return ON;
}

//distance of a point from a line segment
ld distLSP(pt a, pt b, pt c){
	int rpos = relpos(a, b, proj(a, b, c));
	if (rpos == BACK) return abs(c-a);
	if (rpos == FRONT) return abs(c-b);
	b = b-a, c = c-a;
	return abs(b^c/abs(b));
}

//distance between two line segments
ld distLS(pt a, pt b, pt c, pt d){
	if (intersect(a, b, c, d)) return 0;
	return min(min(distLSP(a, b, c), distLSP(a, b, d)), min(distLSP(c, d, a), distLSP(c, d, b)));
}

//angles less than or equal to 180
bool isConvex(vector<pt> &p){
	int n = p.size();
	bool neg = false, pos = false;
	for (int i = 0; i < n; i++){
		int rpos = relpos(p[i], p[(i+1)%n], p[(i+2)%n]);
		if (rpos == LEFT) pos = true;
		if (rpos == RIGHT) neg = true;
	}	
	return (neg&pos) == false;
}

int crossingN(vector<pt> &p, pt a){
	int n = p.size();
	pt b = a;
	for (pt q : p)
		b.x = max(b.x, q.x);
	int cn = 0;
	for (int i = 0; i < n; i++){
		pt q1 = p[i], q2 = p[(i+1)%n];
		if (intersect(a, b, q1, q2) && (dir(a, b, q1) == 1 || dir(a, b, q2) == 1))
			cn++;
	}
	return cn;
}

int windingN(vector<pt> &p, pt a){
	int n = p.size();
	pt b = a;
	for (pt q : p)
		b.x = max(b.x, q.x);
	int wn = 0;
	for (int i = 0; i < n; i++){
		pt q1 = p[i], q2 = p[(i+1)%n];
		if (intersect(a, b, q1, q2)){
			int ps = dir(a, b, q1), qs = dir(a, b, q2);
			if (qs >= 0) wn++;
			if (ps >= 0) wn--;
		}
	}
	return wn;
}

//returns IN, ON or OUT
int pointInPoly(vector<pt> &p, pt a){
	int n = p.size();
	for (int i = 0; i < n; i++)
		if (relpos(p[i], p[(i+1)%n], a) == ON)
			return ON;	
	return (crossingN(p, a)%2 ? IN : OUT);
	//return (windingN(po, a) ? IN : OUT);
}

pair <pt, pt> nearestPair(vector<pt> &po){
	int n = po.size();
	sort(po.begin(), po.end(), cmpXY());
	multiset <pt, cmpYX> s;
	ld rad = abs(po[1]-po[0]);
	pair <pt, pt> res = {po[0], po[1]};
	int l = 0, r = 0;
	for (int i = 0; i < n; i++){
		while (l < r && Geq(po[i].x - po[l].x, rad))
			s.erase(po[l++]);
		while (r < i && Leq(po[r].x, po[i].x))
			s.insert(po[r++]);
		for (auto it = s.lower_bound(pt(po[i].x, po[i].y-rad)); it != s.end(); it++){
			if (Grt(it->y, po[i].y+rad))
				break;
			ld cur = abs(po[i] - (*it));
			if (Lss(cur, rad)){
				rad = cur;
				res = {*it, po[i]};
			}
		}
	}
	return res;
}

//Cuts polygon with line ab and returns the left cut polygon
vector<pt> convexCut(vector<pt> &po, pt a, pt b){
	int n = po.size();
	vector<pt> res;
	for (int i = 0; i < n; i++){
		if (dir(a, b, po[i]) >= 0) 
			res.push_back(po[i]);
		if (abs(dir(a, b, po[i]) - dir(a, b, po[(i+1)%n])) == 2)
			res.push_back(intersection(a, b, po[i], po[(i+1)%n]));
	}
	return res;
}

//Slightly line
pair <pt, pt> get_segment(pt a, pt b){
    const int deltax = b.x - a.x;
    const int deltay = b.y - a.y;
    const int k = 100001;
    pt aa(a.x - k * deltax, a.y - k * deltay);
    pt bb(b.x + deltax, b.y + deltay);
    
    static const int dx[4] = { -1, 0, 1, 0 };
    static const int dy[4] = { 0, 1, 0, -1 };
    for (int d = 0; d < 4; ++d) {
        pt aaa(aa.x + dx[d], aa.y + dy[d]);
        pt bbb(bb.x, bb.y);
        if (dir(aaa, bbb, a) >= 0) continue;
        if (dir(aaa, bbb, b) == 0) continue;
        return {aaa, bbb};
    }
}

pair<int, int> tangent(vector <pt> &A0, vector <pt> &B0){
    vector <pair<pt, int>> A, B;
    for (int i = 0; i < sz(A0); i++)
        A.pb({A0[i], i});
    for (int i = 0; i < sz(B0); i++)
        B.pb({B0[i], i});
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    A = convex_hull(A);
    B = convex_hull(B);
    int ia = 0, ib = 0;
    while (1){
        bool fin = true;
        for (; dir(A[ia].F, B[ib].F, B[(ib+sz(B)-1)%sz(B)].F) < 0 || dir(A[ia].F, B[ib].F, B[(ib+1)%sz(B)].F) < 0; ib = (ib+1)%sz(B))
            fin = false;
        for (; dir(B[ib].F, A[ia].F, A[(ia+sz(A)-1)%sz(A)].F) > 0 || dir(B[ib].F, A[ia].F, A[(ia+1)%sz(A)].F) > 0; ia = (ia+1)%sz(A))
            fin = false;
        if (fin) break;
    }
    return {A[ia].S, B[ib].S};
}

//Sweep Line Example
int main(){	
	vector <pt> adds, rems;
	vector <pair<pt, pt>> query;
	int it;
	cin >> it;
	for (int i = it; i; i--){
		pt p, q;
		cin >> p >> q;
		if (Equ(p.y, q.y)){
			if (Lss(q.x, p.x))
				swap(p, q);
			adds.push_back(p);
			rems.push_back(q);
		}
		else{
			if (Lss(q.y, p.y))
				swap(p, q);
			query.push_back({p, q});
		}
	}
	sort(adds.begin(), adds.end());
	sort(rems.begin(), rems.end());
	sort(query.begin(), query.end());
	multiset <ld> ys;
	int iadd = 0, irem = 0;
	int ans = 0;
	for (auto p : query){
		while (iadd < adds.size() && Leq(adds[iadd].x, p.F.x))
			ys.insert(adds[iadd++].y);
		while (irem < rems.size() && Lss(rems[irem].x, p.F.x) && ys.find(rems[irem].y) != ys.end())
			ys.erase(ys.find(rems[irem++].y));
		int cur = distance(ys.lower_bound(p.F.y), ys.upper_bound(p.S.y));
		ans += cur;
	}
	cout << ans << endl;
	return 0;
}

//rotate b with center=a theta radian
PT rotate(PT a, PT b, ld theta){
	return (b-a)*polar<ld>(1, theta) + a;
}
