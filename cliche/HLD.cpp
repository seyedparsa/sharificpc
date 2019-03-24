//atcoder grand 14 E
#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

#define F first
#define S second
#define tm lkajsdf

const int MAXN = 1e5 + 10;
const int LOG = 18;

int n, s_t[MAXN], tm, par[MAXN][LOG], depth[MAXN], sub[MAXN];
int id[MAXN], ppp[MAXN];
vector<int> adj[MAXN];

bool cmp(int u, int v){return sub[u] > sub[v];}
void plant(int v, int p = -1){
	if (~p)
		adj[v].erase(find(adj[v].begin(), adj[v].end(), p));
	sub[v] = 1;
	for (int u:adj[v])
		plant(u, v), sub[v] += sub[u];
	sort(adj[v].begin(), adj[v].end(), cmp);
}

int cur = 0, pp = -1;
void dfs(int v, int p = -1, int de = 0){
	if (cur == 0) pp = p;
	id[v] = ++cur;
	ppp[v] = pp;
	par[v][0] = p;
	s_t[v] = tm++;
	depth[v] = de;
	for (int u:adj[v])
		dfs(u, v, de+1);
	cur = 0;
}

void init(){
	for (int w = 1; w < LOG; w++)
		for (int v = 0; v < n; v++)
			if (~par[v][w - 1])
				par[v][w] = par[par[v][w - 1]][w - 1];
			else
				par[v][w] = par[v][w - 1];

}

int lca(int u, int v){
	if (depth[u] < depth[v]) swap(u, v);
	for (int w = LOG-1; ~w; w--)
		if (depth[u] - (1<<w) >= depth[v])
			u = par[u][w];
	if (u == v) return u;

	for (int w = LOG-1; ~w; w--)
		if (par[v][w] ^ par[u][w])
			v = par[v][w], u = par[u][w];
	return par[v][0];
}

int lz[MAXN<<2];
pii mn[MAXN<<2];
set<int> st[MAXN<<2];
void ins(int v, int b, int e, int l, int r, int val, bool tp=1){
	if (l <= b && e <= r){
		if (tp)
			st[v].insert(val);
		else
			st[v].erase(val);
		return;
	}
	if (r <= b || e <= l) return;

	int mid = b + e >> 1;
	ins(v<<1, b, mid, l, r, val, tp);
	ins(v<<1^1, mid, e, l, r, val, tp);
}

void absorb(int v){
	if (!lz[v]) return;
	mn[v<<1].F += lz[v];
	lz[v<<1] += lz[v];
	mn[v<<1^1].F += lz[v];
	lz[v<<1^1] += lz[v];
	lz[v] = 0;
}

void water(int v, int b, int e, int l, int r, int val){
	if (l <= b && e <= r){
		mn[v].F += val;
		lz[v] += val;
		return;
	}
	if (r <= b || e <= l) return;

	int mid = b + e >> 1;
	absorb(v);
	water(v<<1, b, mid, l, r, val);
	water(v<<1^1, mid, e, l, r, val);
	mn[v] = min(mn[v<<1], mn[v<<1^1]);
}

void add(int v, int p, int x, int val, bool tp=1){
	while (v^p){
		if (depth[v] - id[v] >= depth[p]){
			ins(1, 0, n, s_t[v] + 1 - id[v], s_t[v]+1, x, tp);
			water(1, 0, n, s_t[v] + 1 - id[v], s_t[v]+1, val);
			v = ppp[v];
		}
		else{
			ins(1, 0, n, s_t[v] + 1 - (depth[v] - depth[p]), s_t[v]+1, x, tp);
			water(1, 0, n, s_t[v] + 1 - (depth[v] - depth[p]), s_t[v]+1, val);
			break;
		}
	}
}

void build(int v, int b, int e){
	mn[v] = {0, b};
	if (e - b == 1) return;

	int mid = b + e >> 1;
	build(v<<1, b, mid);
	build(v<<1^1, mid, e);
	mn[v] = min(mn[v<<1], mn[v<<1^1]);
}

int get(int v, int b, int e, int pos){
	if (st[v].size()) return *st[v].begin();

	int mid = b + e >> 1;
	if (pos < mid)
		return get(v<<1, b, mid, pos);
	return get(v<<1^1, mid, e, pos);
}

int uu[MAXN], vv[MAXN];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for (int i = 0; i < n - 1; i++){
		int a, b;	cin >> a >> b, a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	plant(0);
	dfs(0);
	init();
	build(1, 0, n);
	
	water(1, 0, n, 0, 1, (int)1e9);
	for (int i = 0; i < n - 1; i++){
		cin >> uu[i] >> vv[i], uu[i]--, vv[i]--;
		int p = lca(uu[i], vv[i]);
		add(vv[i], p, i, 1);
		add(uu[i], p, i, 1);
	}
	for (int i = 0; i < n - 1; i++){
		auto x = mn[1];
	//	cout << x.F << " " << x.S << endl;
		if (x.F != 1){
			cout << "NO\n";
			return 0;
		}

		int ind = get(1, 0, n, x.S);
		int p = lca(uu[ind], vv[ind]);
		add(vv[ind], p, ind, -1, 0);
		add(uu[ind], p, ind, -1, 0);
		water(1, 0, n, x.S, x.S+1, (int)1e9);
	}
	cout << "YES\n";
	return 0;
}

