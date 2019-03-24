int n;
vector<int> adj[MAXN];
int from[MAXE], to[MAXE];
int sec[MAXE], sz;
bool del[MAXE];

void dfs(int v, int p = -1){
	while (adj[v].size()){
		int e = adj[v].back();
		adj[v].pop_back();
		if (del[e]) continue;

		del[e] = true;
		if (from[e] != v)
			swap(from[e], to[e]);
		dfs(to[e], e);
	}
	if (~p)
		sec[sz++] = p;
}
