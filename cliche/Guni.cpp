int n, sub[MAXN];
vector<int> adj[MAXN];

bool cmp(int u, int v){return sub[u] > sub[v];}

void plant(int v, int p = -1){
	sub[v] = 1;
	if (!p)
		adj[v].erase(find(adj[v].begin(), adj[v].end(), p));
	for (int u:adj[v])
		plant(u, v), sub[v] += sub[u];
	sort(adj[v].begin(), adj[v].end());
}

void add(int v){

}

void dfs(int v, bool type = 1){
	for (int i = 1; i < adj[v].size(); i++) dfs(adj[v][i], 0);
	if (adj[v].size())
		dfs(adj[v][0]);
	for (int i = 1; i < adj[v].size(); i++)
		add(adj[v][i]);

	if (!keep){
		//clean up
	}
}
