const int N = -1;
const int L = -1;

int lca(int u, int v)
{
	if (h[u] < h[v])
		swap(u, v);
	int dif = h[u] - h[v];
	for (int i = 0; i < L; i++)
		if (dif>>i&1)
			u = par[u][i];
	if (u == v) return u;
	for (int i = L-1; i >= 0; i--)
		if (par[u][i] != par[v][i]){
			u = par[u][i];
			v = par[v][i];
		}
	return par[u][0];
}

void dfs(int v, int p)
{
	par[v][0] = p;
	for (int i = 1; i < L; i++)
		par[v][i] = par[par[v][i-1]][i-1];
	for (int u : adj[v]){
		if (u == p) continue;
		h[u] = h[v] + 1;
		dfs(u, v);
	}
}

int main(){
	h[0] = 0;
	dfs(0, 0);
}
