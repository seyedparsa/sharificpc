int n, sub[MAXN];
vector<int> adj[MAXN];
set<int> st;

bool cmp(int u, int v){return sub[u] > sub[v];}

void plant(int v, int p = -1){
	if (~p)
		adj[v].erase(find(adj[v].begin(), adj[v].end(), p));
	sub[v] = 1;
	for (int u:adj[v])
		plant(u, v), sub[v] += sub[u];
	sort(adj[v].begin(), adj[v].end(), cmp);
}

void go(int v){
	for (int u:adj[v]) go(u);
	if (adj[v].size())
		st[v].swap(st[adj[v][0]]);

	auto hint = st[v].begin();
	for (int u:adj[v]){
		for (int x:st[u])
			hint = st[v].insert(hint, x);
		st[u].clear();
	}
}
