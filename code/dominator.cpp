struct DominatorTree{
	vector<int> adj[MAXN], radj[MAXN], tree[MAXN], bucket[MAXN]; // SET MAXIMUM NUMBER OF NODES
	int sdom[MAXN], par[MAXN], idom[MAXN], dsu[MAXN], label[MAXN];
	int arr[MAXN], rev[MAXN], cnt;
	void clear(){
		for (int i = 0; i < MAXN; i++){
			adj[i].clear();
			radj[i].clear();
			tree[i].clear();
			sdom[i] = idom[i] = dsu[i] = label[i] = i;
			arr[i] = -1;
		}
		cnt = 0;
	}
	void add_edge(int u, int v){
		adj[u].push_back(v);
	}
	void dfs(int v){
		arr[v] = cnt;
		rev[cnt] = v;
		cnt++;
		for (int i = 0; i < adj[v].size(); i++){
			int u = adj[v][i];
			if (arr[u] == -1){
				dfs(u);
				par[arr[u]] = arr[v];
			}
			radj[arr[u]].push_back(arr[v]);
		}
	}
	int find(int v, int x = 0){
		if (dsu[v] == v)
			return (x ? -1 : v);
		int u = find(dsu[v], x + 1);
		if (u < 0)
			return v;
		if (sdom[label[dsu[v]]] < sdom[label[v]])
			label[v] = label[dsu[v]];
		dsu[v] = u;
		return (x ? u : label[v]);
	}
	void merge(int u, int v){
		dsu[v] = u;
	}
	void build(int root){
		dfs(root);
		int n = cnt;
		for (int v = n - 1; v >= 0; v--){
			for (int i = 0; i < radj[v].size(); i++){
				int u = radj[v][i];
				sdom[v] = min(sdom[v], sdom[find(u)]);
			}
			if (v > 0)
				bucket[sdom[v]].push_back(v);
			for (int i = 0; i < bucket[v].size(); i++){
				int u = bucket[v][i];
				int w = find(u);
				if (sdom[u] == sdom[w])
					idom[u] = sdom[u];
				else
					idom[u] = w;
			}
			if (v > 0)
				merge(par[v], v);
		}
		for (int v = 1; v < n; v++){
			if (idom[v] != sdom[v])
				idom[v] = idom[idom[v]];
			tree[rev[v]].push_back(rev[idom[v]]);
			tree[rev[idom[v]]].push_back(rev[v]);
		}
	}
	DominatorTree(){
		clear();
	}
};
