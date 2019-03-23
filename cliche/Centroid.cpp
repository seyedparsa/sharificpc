int n, sub[MAXN];
vector<int> adj[MAXN];
bool blocked[MAXN];

void plant(int v, int p = -1){
	sub[v] = 1;
	for (int u:adj[v])
		if (u^p && !blocked[u])
			plant(u, v), sub[v] += sub[u];
}

void go(int v, char cur){
	plant(v);
	int p = -1, tot = sub[v], changed = 1;
	while (changed){
		changed = 0;
		for (int u:adj[v])
			if (u^p && !blocked[u] && sub[u]*2 > tot){
				p = v;
				v = u;
				changed = 1;
				break;
			}
	}

	ans[v] = cur;
	blocked[v] = true;
	for (int u:adj[v])
		if (!blocked[u])
			go(u, cur+1);
	blocked[v] = false;

	//solve for v
}
