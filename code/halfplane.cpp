typedef int T;
typedef long long T2;
typedef long long T4; // maybe int128_t 

const int MAXLINES = 100 * 1000 + 10;
const int INF = 20 * 1000 * 1000;

typedef pair<T, T> point;
typedef pair<point, point> line;

#define X first
#define Y second
#define A first
#define B second

// REPLACE ZERO WITH EPS FOR DOUBLE

point operator - (const point &a, const point &b) {
	return point(a.X - b.X, a.Y - b.Y);
}


T2 cross(point a, point b) {
	return ((T2)a.X * b.Y - (T2)a.Y * b.X);
}

bool cmp(line a, line b) {
	bool aa = a.A < a.B;
	bool bb = b.A < b.B;
	if (aa == bb) {
		point v1 = a.B - a.A;
		point v2 = b.B - b.A;
		if (cross(v1, v2) == 0)
			return cross(b.B - b.A, a.A - b.A) > 0;
		else
			return cross(v1, v2) > 0;
	}
	else
		return aa;
}

bool parallel(line a, line b) {
	return cross(a.B - a.A, b.B - b.A) == 0;
}

pair<T2, T2> alpha(line a, line b) {
	return pair<T2, T2>(cross(b.A - a.A, b.B - b.A),
						cross(a.B - a.A, b.B - b.A));
}

bool fcmp(T4 f1t, T4 f1b, T4 f2t, T4 f2b) {
	if (f1b < 0) {
		f1t *= -1;
		f1b *= -1;
	}
	if (f2b < 0) {
		f2t *= -1;
		f2b *= -1;
	}
	return f1t * f2b < f2t * f1b; // check with eps
}

bool check(line a, line b, line c) {
	bool crs = cross(c.B - c.A, a.B - a.A) > 0;
	pair<T2, T2> a1 = alpha(a, b);
	pair<T2, T2> a2 = alpha(a, c);
	bool alp = fcmp(a1.A, a1.B, a2.A, a2.B);
	return (crs ^ alp);
}

bool notin(line a, line b, line c) { // is intersection of a and b in ccw direction of c?
	if (parallel(a, b))
		return false;
	if (parallel(a, c))
		return cross(c.B - c.A, a.A - c.A) < 0;
	if (parallel(b, c))
		return cross(c.B - c.A, b.A - c.A) < 0;
	return !(check(a, b, c) && check(b, a, c));
}

void print(vector<line> lines) {
	cerr << " @ @ @ " << endl;
	for (int i = 0; i < lines.size(); i++)
		cerr << lines[i].A.X << " " << lines[i].A.Y << " -> " << lines[i].B.X << " " << lines[i].B.Y << endl;
	cerr << " @ @ @ " << endl<< endl;
}

line dq[MAXLINES];

vector<line> half_plane(vector<line> lines) {
	lines.push_back(line(point(INF, -INF), point(INF, INF)));
	lines.push_back(line(point(-INF, INF), point(-INF, -INF)));
	lines.push_back(line(point(-INF, -INF), point(INF, -INF)));
	lines.push_back(line(point(INF, INF), point(-INF, INF)));
	sort(lines.begin(), lines.end(), cmp);
	int ptr = 0;
	for (int i = 0; i < lines.size(); i++)
		if (i > 0 && 
			(lines[i - 1].A < lines[i - 1].B) == (lines[i].A < lines[i].B) && 
			parallel(lines[i - 1], lines[i]))
			continue;
		else
			lines[ptr++] = lines[i];
	lines.resize(ptr);
	if (lines.size() < 2)
		return lines;
	//print(lines);
	int f = 0, e = 0;
	dq[e++] = lines[0];
	dq[e++] = lines[1];
	for (int i = 2; i < lines.size(); i++) {
		while (f < e - 1 && notin(dq[e - 2], dq[e - 1], lines[i]))
			e--;
		//print(vector<line>(dq + f, dq + e));
		if (e == f + 1) {
			T2 crs = cross(dq[f].B - dq[f].A, lines[i].B - lines[i].A) ;
			if (crs < 0)
				return vector<line>();
			else if (crs == 0 && cross(lines[i].B - lines[i].A, dq[f].B - lines[i].A) < 0)
				return vector<line>();
		}
		while (f < e - 1 && notin(dq[f], dq[f + 1], lines[i]))
			f++;
		dq[e++] = lines[i];
	}
	while (f < e - 1 && notin(dq[e - 2], dq[e - 1], dq[f]))
		e--;
	while (f < e - 1 && notin(dq[f], dq[f + 1], dq[e - 1]))
		f++;
	vector<line> res;
	res.resize(e - f);
	for (int i = f; i < e; i++)
		res[i - f] = dq[i];
	return res;
}


int main() {
	int n;
	cin >> n;
	vector<line> lines;
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		lines.push_back(line(point(x1, y1), point(x2, y2)));
	}
	lines = half_plane(lines);
	cout << lines.size() << endl;
	for (int i = 0; i < lines.size(); i++)
		cout << lines[i].A.X << " " << lines[i].A.Y << " " << lines[i].B.X << " " << lines[i].B.Y << endl;
}
