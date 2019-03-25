const int MAXN = 100 * 1000 + 10;
const int MAXLG = 20;
const int INF = 100 * 1000 * 1000 + 10;
const int MAXPOINTS = MAXN * MAXLG;
typedef pair<int ,int> point;
struct tria{
	int a, b, c;
	tria(int _a, int _b, int _c){
		a = _a; b = _b; c = _c;
	}
	tria(){a = b = c = 0;}
};
struct Delaunay {
	typedef pair<point, int> ppi;
	typedef pair<int, int> pii;
	typedef pair<pii, int> pip;
	tria t[MAXPOINTS];
	bool mrk[MAXPOINTS];
	int last[MAXPOINTS];
	int childs[MAXPOINTS][3];
	int cnt;
	vector<ppi> points;
	set<pip> edges;
	vector<tria> res;
	int n;
	inline void add_edge(int a, int b, int c){
		edges.insert(pip(pii(min(a, b), max(a, b)), c));
	}
	inline void remove_edge(int a, int b, int c){
		edges.erase(pip(pii(min(a, b), max(a, b)), c));
	}
	int add_triangle(int a, int b, int c){
		if (cross(points[b].first - points[a].first, points[c].first - points[a].first) == 0)
			return -1;
		if (cross(points[b].first - points[a].first, points[c].first - points[a].first) < 0)
			swap(b, c);
		add_edge(a, b, cnt);
		add_edge(b, c, cnt);
		add_edge(c, a, cnt);
		t[cnt] = tria(a, b, c);
		childs[cnt][0] = childs[cnt][1] = childs[cnt][2] = -1;
		mrk[cnt] = false;
		last[cnt] = -1;
		cnt++;
		return cnt - 1;
	}
	inline void remove_triangle(int v){
		childs[v][0] = childs[v][1] = childs[v][2] = -1;
		remove_edge(t[v].a, t[v].b, v);
		remove_edge(t[v].b, t[v].c, v);
		remove_edge(t[v].c, t[v].a, v);
	}
	inline void relax_edge(const int &a, const int &b){
		pii key(min(a, b), max(a, b));
		set<pip>::iterator it = edges.lower_bound(pip(key, -1));
		if (it == edges.end() || it->first != key)
			return;
		set<pip>::iterator it2 = it;
		it2++;
		if (it2 == edges.end() || it2->first != key)
			return;
		int c1 = t[it->second].a + t[it->second].b + t[it->second].c - a - b;
		int c2 = t[it2->second].a + t[it2->second].b + t[it2->second].c - a - b;
		if (c1 > n || c2 > n)
			return;
		if (inCircle(points[a].first, points[b].first, points[c1].first, points[c2].first) < 0 || 
				inCircle(points[a].first, points[b].first, points[c2].first, points[c1].first) < 0)
		{
			int v1 = it->second;
			int v2 = it2->second;
			remove_triangle(v1);
			remove_triangle(v2);
			mrk[v1] = mrk[v2] = true;
			childs[v1][0] = childs[v2][0] = add_triangle(a, c1, c2);
			childs[v1][1] = childs[v2][1] = add_triangle(b, c1, c2);
			relax(childs[v1][0]);
			relax(childs[v1][1]);
		}
	}
	inline void relax(int v){
		relax_edge(t[v].a, t[v].b);
		relax_edge(t[v].b, t[v].c);
		relax_edge(t[v].c, t[v].a);
	}
	inline bool inLine(int a, int b, int c){
		return cross(points[b].first - points[a].first, points[c].first - points[a].first) >= 0;
	}
	inline bool inTriangle(int a, int b, int c, int d){
		return inLine(a, b, d) && inLine(b, c, d) && inLine(c, a, d);
	}
	void find(int v, int p, int cl){
		if (last[v] == cl)
			return;
		bool reached = false;
		last[v] = cl;
		for (int i = 0; i < 3; i++)
		{
			int u = childs[v][i];
			if (u == -1)
				continue;
			reached = true;
			if (mrk[u] || inTriangle(t[u].a, t[u].b, t[u].c, p))
				find(u, p, cl);
		}
		if (reached)
			return ;
		remove_triangle(v);
		childs[v][0] = add_triangle(p, t[v].a, t[v].b);
		childs[v][1] = add_triangle(p, t[v].b, t[v].c);
		childs[v][2] = add_triangle(p, t[v].c, t[v].a);
		relax(childs[v][0]);
		relax(childs[v][1]);
		relax(childs[v][2]);
	}
	void getRes(int v, int cl){
		if (last[v] == cl)
			return;
		last[v] = cl;
		bool reached = false;
		for (int i = 0; i < 3; i++)
		{
			int u = childs[v][i];
			if (u == -1)
				continue;
			reached = true;
			getRes(u, cl);
		}
		if (!reached && t[v].a < n && t[v].b < n && t[v].c < n)
			res.push_back(t[v]);
	}
    vector<tria> delaunay(vector<point> v){
		cnt = 0;
		int cl = 0;
		points.clear();
		for (int i = 0; i < v.size(); i++)
			points.push_back(ppi(v[i], i));
		random_shuffle(points.begin(), points.end());
		n = points.size();
		points.push_back(ppi(point(INF, INF), n));
		points.push_back(ppi(point(-INF * 3, INF), n + 1));
		points.push_back(ppi(point(INF, -INF * 3), n + 2));
		int root = add_triangle(n, n + 1, n + 2);
		for (int i = 0; i < n; i++){
			//	cout << "@@@@@@@@@@" << inTriangle(n,n+1, n+2, i) << endl;
			find(root, i, cl++);
		}
		res.clear();
		getRes(root, cl++);
		for (int i = 0; i < res.size(); i++){
			res[i].a = points[res[i].a].second;
			res[i].b = points[res[i].b].second;
			res[i].c = points[res[i].c].second;
		}
		return res;
	}
};
long double getRadius(pointD a, pointD b, pointD c){
	pointD v1 = norm(b - a) + ((a + b) / 2);
	pointD v2 = norm(c - b) + ((b + c) / 2);
	pointD center =  intersect((a + b) / 2, v1, (b + c) / 2, v2);
	pointD ret = a - center;
	return sqrt(dot(ret, ret));
}
Delaunay d;
int main(){
	srand(2019);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	vector<point> v;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		v.push_back(point(x, y));
	}
	vector<tria> ans = d.delaunay(v);
	long double res = 0;
	for (int i = 0; i < ans.size(); i++)
		res = max(res, getRadius(v[ans[i].a], v[ans[i].b], v[ans[i].c]));
	cout.precision(6);
	cout << fixed << res << endl;
}
