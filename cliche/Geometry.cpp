
//be naame khodaa
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair <int, int> pii;
#define F first
#define S second

inline int in(){int X, Y; Y = scanf("%d", &X); return X; }

const int N = -1;
const ld EPS = 1e-12;

bool eq(ld a, ld b){
	return abs(a-b) < EPS;
}

struct PT{
	ld X, Y;
	PT (ld X = 0, ld Y = 0) : X(X), Y(Y) {}
	PT operator + (PT ro) const{
		return PT(X+ro.X, Y+ro.Y);
	}
	PT operator - (PT ro) const{
		return PT(X-ro.X, Y-ro.Y);
	}
	PT operator * (ld co) const{
		return PT(X*co, Y*co);
	}
	PT operator / (ld co) const{
		return PT(X/co, Y/co);
	}
	ld operator * (PT ro) const{
		return X*ro.X + Y*ro.Y;
	}
	ld operator ^ (PT ro) const{
		return X*ro.Y - Y*ro.X;
	}
	void operator -= (PT ro){
		(*this) = (*this) - ro;
	}
};

istream& operator>> (istream &is, PT &p){
	ld val;
	is >> val;
	p.X = val;
	is >> val;
	p.Y = val;
	return is;
}

PT operator * (ld co, PT p){
	return p*co;
}

ld len(PT a){
	return sqrt(a*a);
}

PT unit(PT a){
	return a/len(a);
}

PT clrot(PT a){
	return PT(-a.Y, a.X);
}

PT proj(PT a, PT b, PT c){
	b = b-a, c = c-a;
	return a + (b*c)/(b*b)*b;
}

PT reflect(PT a, PT b, PT c){
	PT d = c;
	b = b-a, c = c-a;
	return d + (c^b)/len(b)*clrot(unit(b))*2;
}

int side(PT a, PT b, PT c){
	ld cr = (b-a)^(c-a);
	return cr > EPS ? 1 : (cr + EPS < 0 ? -1 : 0);
}

bool intersect(PT a, PT b, PT c, PT d){
	int as = side(c, d, a),
		bs = side(c, d, b),
		cs = side(a, b, c),
		ds = side(a, b, d);
	if (as && as == bs || cs && cs == ds)
		return false;
	else if (as || bs || cs || ds)
		return true;
	for (int j = 0; j < 2; j++){
		ld mX = min(a.X, b.X),
		   MX = max(a.X, b.X),
		   mY = min(a.Y, b.Y),
		   MY = max(a.Y, b.Y);
		for (int k = 0; k < 2; k++){
			if (c.X + EPS > mX && c.X < MX + EPS && c.Y + EPS > mY && c.Y < MY + EPS)
				return true;
			swap(c, d);
		}
		swap(a, c);
		swap(b, d);
	}
	return false;
}

PT intersection(PT a, PT b, PT c, PT d){
	ld c1 = (b-a)^(c-a), c2 = (b-a)^(d-a);
	return (c1*d - c2*c)/(c1 - c2);
}

int main(){
	cout << setprecision(10) << fixed;
	Poly p;
	for (int i = in(); i; i--){
		PT a, b, c, d;
		cin >> a >> b >> c >> d;
		PT o = intersection(a, b, c, d);
		cout << o.X << ' ' << o.Y << '\n';
	}
	return 0;
}
