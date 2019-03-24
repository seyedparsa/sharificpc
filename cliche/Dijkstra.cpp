const int N = 200002;
const int INF = 1e9+1;

int n, m, d[N];
vector <pii> adj[N];
set<pii> st;

void update(int v){
	for (auto e:adj[v]){
		int u = e.F, w = e.S;
		if (d[v]+w < d[u]){
			st.erase({d[u], u});
			d[u] = d[v]+w;
			st.insert({d[u], u});
		}
	}
}

void dijk(int v){
	fill(d, d+n, INF);
	d[v] = 0;
	st.insert({d[v], v});
	while (st.size()) {
		int v = st.begin()->S;
		st.erase(st.begin());
		update(v);
	}
}
