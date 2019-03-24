
//be naame khodaa
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair <int, int> pii;
typedef complex<ld> PT;
typedef vector<PT> Poly;
typedef pair<PT, PT> LS;
#define F first
#define S second
#define X real()
#define Y imag()
#define pb push_back

inline int in(){int x, y; y = scanf("%d", &x); return x; }

const ld EPS = 1e-12;

const int ON = 0, LEFT = 1, RIGHT = -1, BACK = -2, FRONT = 2, IN = 3, OUT = -3;

inline bool Geq(ld a, ld b){ return a - b > -EPS; }
inline bool Grt(ld a, ld b){ return a - b > EPS; }
inline bool Leq(ld a, ld b){ return a - b < EPS; }
inline bool Lss(ld a, ld b){ return a - b < -EPS; }
inline bool Equ(ld a, ld b){ return abs(a-b) < EPS; }

istream& operator>> (istream& is, complex<ld>& p){
	ld val; is >> val; p.real(val); is >> val; p.imag(val); return is;
}
bool byX(const PT &a, const PT &b){
	if (Equ(a.X, b.X)) return Lss(a.Y, b.Y);
	return Lss(a.X, b.X);
}
bool byY(const PT &a, const PT &b){
	if (Equ(a.Y, b.Y)) return Lss(a.X, b.X);
	return Lss(a.Y, b.Y);
}
struct cmpXY{ bool operator ()(const PT &a, const PT &b){ return byX(a, b); } };
struct cmpYX{ bool operator ()(const PT &a, const PT &b){ return byY(a, b); } };

ld dot(PT a, PT b){ return real(conj(a)*b); }
ld cross(PT a, PT b){ return imag(conj(a)*b); }
ld sqlen(PT a){ return dot(a, a); }
ld len(PT a){ return sqrt(sqlen(a)); }

//projection of c on ab
PT proj(PT a, PT b, PT c){
	b -= a, c -= a;
	return a + b*real(c/b);
}

//reflection of c toward ab
PT reflect(PT a, PT b, PT c){
	b -= a, c -= a;
	return a + conj(c/b)*b;
}

//rotate b with center=a theta radian
PT rotate(PT a, PT b, ld theta){
	return (b-a)*polar<ld>(1, theta) + a;
}

//relative position of c toward ab
int relpos(PT a, PT b, PT c){
	b -= a; c -= a; c /= b;
	if (Grt(c.imag(), 0)) return LEFT;
	if (Lss(c.imag(), 0)) return RIGHT;
	if (Lss(c.real(), 0)) return BACK;
	if (Grt(c.real(), 1)) return FRONT;
	return ON;
}

//sign of cross product of ab and ac
int side(PT a, PT b, PT c){
	b -= a, c -= a;
	ld cr = (c/b).Y;
	return Grt(cr, 0) ? 1 : (Lss(cr, 0) ? -1 : 0);
}

//if two line segments intersect
bool intersect(PT a, PT b, PT c, PT d){
	int as = side(c, d, a), bs = side(c, d, b), cs = side(a, b, c), ds = side(a, b, d);
	if (as && as == bs || cs && cs == ds) return false;
	else if (as || bs || cs || ds) return true;
	for (int j = 0; j < 2; j++, swap(a, c), swap(b, d)){
		ld mx = min(a.X, b.X), Mx = max(a.X, b.X), my = min(a.Y, b.Y), My = max(a.Y, b.Y);
		for (int k = 0; k < 2; k++, swap(c, d))
			if (Geq(c.X, mx) && Leq(c.X, Mx) && Geq(c.Y, my) && Leq(c.Y, My))
				return true;
	}
	return false;
}

//intersection of two non-parallel lines
PT intersection(PT a, PT b, PT c, PT d){
	ld c1 = cross(b-a, c-a), c2 = cross(b-a, d-a);
	return (c1*d - c2*c)/(c1-c2);
}

//distance of a point from a line segment
ld distLSP(PT a, PT b, PT c){
	int rpos = relpos(a, b, proj(a, b, c));
	if (rpos == BACK) return len(c-a);
	if (rpos == FRONT) return len(c-b);
	b -= a, c -= a;
	return abs(cross(b, c)/len(b));
}

//distance between two line segments
ld distLS(PT a, PT b, PT c, PT d){
	if (intersect(a, b, c, d)) return 0;
	return min(min(distLSP(a, b, c), distLSP(a, b, d)), min(distLSP(c, d, a), distLSP(c, d, b)));
}

ld signedArea(Poly &po){
	int n = po.size();
	ld res = 0;
	for (int i = 0; i < n; i++)
		res += cross(po[i], po[(i+1)%n]);
	return res/2;
}

ld area(Poly &poly){
	return abs(signedArea(poly));
}

//angles less than or equal to 180
bool isConvex(Poly &po){
	int n = po.size();
	bool neg = false, pos = false;
	for (int i = 0; i < n; i++){
		int rpos = relpos(po[i], po[(i+1)%n], po[(i+2)%n]);
		if (rpos == LEFT) pos = true;
		if (rpos == RIGHT) neg = true;
	}	
	return (neg&pos) == false;
}

int crossingN(Poly &po, PT a){
	int n = po.size();
	PT b = a;
	for (PT p : po)
		b.real(max(b.X, p.X));
	int cn = 0;
	for (int i = 0; i < n; i++){
		PT p = po[i], q = po[(i+1)%n];
		if (intersect(a, b, p, q) && (side(a, b, p) == 1 || side(a, b, q) == 1))
			cn++;
	}
	return cn;
}

int windingN(Poly &po, PT a){
	int n = po.size();
	PT b = a;
	for (PT p : po)
		b.real(max(b.X, p.X));
	int wn = 0;
	for (int i = 0; i < n; i++){
		PT p = po[i], q = po[(i+1)%n];
		if (intersect(a, b, p, q)){
			int ps = side(a, b, p), qs = side(a, b, q);
			if (qs >= 0) wn++;
			if (ps >= 0) wn--;
		}
	}
	return wn;
}

//returns IN, ON or OUT
int pointInPoly(Poly &po, PT a){
	int n = po.size();
	for (int i = 0; i < n; i++)
		if (relpos(po[i], po[(i+1)%n], a) == ON)
			return ON;	
	return (crossingN(po, a)%2 ? IN : OUT);
	//return (windingN(po, a) ? IN : OUT);
}

Poly getHull(Poly &po, bool lower){
	sort(po.begin(), po.end(), cmpXY());
	Poly res;
	int n = res.size();
	for (auto p : po){
		while (n >= 2 && side(res[n-2], res[n-1], p) == (lower ? RIGHT : LEFT))
			res.pop_back(), n--;
		res.pb(p), n++;
	}
	return res;
}

Poly convexHull(Poly &po){
	int n = po.size();
	Poly lower = getHull(po, true),
		 upper = getHull(po, false);
	Poly res = lower;
	for (int i = (int)upper.size()-2; i; i--)
		res.pb(upper[i]);
	return res;
}

//Given some points (at least two)
pair <PT, PT> nearestPair(Poly &po){
	int n = po.size();
	sort(po.begin(), po.end(), cmpXY());
	multiset <PT, cmpYX> s;
	ld rad = len(po[1]-po[0]);
	pair <PT, PT> res = {po[0], po[1]};
	int l = 0, r = 0;
	for (int i = 0; i < n; i++){
		while (l < r && Geq(po[i].X - po[l].X, rad))
			s.erase(po[l++]);
		while (r < i && Leq(po[r].X, po[i].X))
			s.insert(po[r++]);
		for (auto it = s.lower_bound(PT(po[i].X, po[i].Y-rad)); it != s.end(); it++){
			if (Grt(it->Y, po[i].Y+rad))
				break;
			ld cur = len(po[i] - (*it));
			if (Lss(cur, rad)){
				rad = cur;
				res = {*it, po[i]};
			}
		}
	}
	return res;
}

//Given Convex Polygon having at least one point
pair <PT, PT> farthestPair(Poly &po){
	int n = po.size();
	pair <PT, PT> res = {po[0], po[0]};
	int j = 0;
	for (int i = 0; i < n; i++){
		while (Grt(len(po[(j+1)%n] - po[i]), len(po[j] - po[i])))
			j = (j+1)%n;
		if (Grt(len(po[j]-po[i]), len(res.S-res.F)))
			res = {po[i], po[j]};
	}
	return res;
}

ld diameter(Poly &po){
	auto p = farthestPair(po);
	return len(p.S-p.F);
}

ld radius(Poly &po){
	auto p = nearestPair(po);
	return len(p.S-p.F);
}

//Cuts polygon with line ab and returns the left cut polygon
Poly convexCut(Poly &po, PT a, PT b){
	int n = po.size();
	Poly res;
	for (int i = 0; i < n; i++){
		if (side(a, b, po[i]) >= 0) 
			res.pb(po[i]);
		if (abs(side(a, b, po[i]) - side(a, b, po[(i+1)%n])) == 2)
			res.pb(intersection(a, b, po[i], po[(i+1)%n]));
	}
	return res;
}

//Sweep Line Example
int main(){	
	vector <PT> adds, rems;
	vector <LS> query;
	for (int i = in(); i; i--){
		PT p, q;
		cin >> p >> q;
		if (Equ(p.Y, q.Y)){
			if (Lss(q.X, p.X))
				swap(p, q);
			adds.pb(p);
			rems.pb(q);
		}
		else{
			if (Lss(q.Y, p.Y))
				swap(p, q);
			query.pb({p, q});
		}
	}
	sort(adds.begin(), adds.end(), [](PT a, PT b){ return byX(a, b); });
	sort(rems.begin(), rems.end(), [](PT a, PT b){ return byX(a, b); });
	sort(query.begin(), query.end(), [](LS a, LS b){ return byX(a.F, b.F); });
	multiset <ld> ys;
	int iadd = 0, irem = 0;
	int ans = 0;
	for (auto p : query){
		while (iadd < adds.size() && Leq(adds[iadd].X, p.F.X))
			ys.insert(adds[iadd++].Y);
		while (irem < rems.size() && Lss(rems[irem].X, p.F.X) && ys.find(rems[irem].Y) != ys.end())
			ys.erase(ys.find(rems[irem++].Y));
		int cur = distance(ys.lower_bound(p.F.Y), ys.upper_bound(p.S.Y));
		ans += cur;
	}
	cout << ans << endl;
}
