const int N = 200002;

int par[N], sz[N];

int root(int v) { return par[v] == -1 ? v : par[v] = root(par[v]); }

// returns true if u, v are from different components
bool merge(int u, int v) {
	u = root(u);
	v = root(v);
	if(u == v)
		return false;
	if(sz[u] < sz[v])
		swap(u, v);
	sz[u] += sz[v];
	par[v] = u;
	return true;
}

int main(){
	int n = in();
	fill(par, par + n, -1);
	fill(sz, sz + n, 1);
}

