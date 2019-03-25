vector<int> adj[maxn];
bool vis[maxn];
int dep[maxn], par[maxn], lowlink[maxn];
vector<vector<int> > comp;
stack<int> st;
void dfs(int u, int depth = 0, int parent = -1){
	vis[u] = true;
	dep[u] = depth;
	par[u] = parent;
	lowlink[u] = depth;
	st.push(u);
	for (int i = 0; i < adj[u].size(); i++){
		int v = adj[u][i];
		if (!vis[v])
		{
			dfs(v, depth + 1, u);
			lowlink[u] = min(lowlink[u], lowlink[v]);
		}
		else
			lowlink[u] = min(lowlink[u], dep[v]);
	}
	if (lowlink[u] == dep[u] - 1){
		comp.push_back(vector<int>());
		while (st.top() != u)
		{
			comp.back().push_back(st.top());
			st.pop();
		}
		comp.back().push_back(u);
		st.pop();
		comp.back().push_back(par[u]);
	}
}
void bicon(int n){
	for (int i = 0; i < n; i++)
		if (!vis[i])
			dfs(i);
}
