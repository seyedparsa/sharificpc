const int N = 200002;

int comp[N];
vector <int> g[N], h[N];
bool mark[N];

void addE(int u, int v)
{
	g[u].push_back(v);
	h[v].push_back(u);
}

void dfs(int v, vector <int> *g, vector <int> &nodes)
{
	mark[v] = 1;
	for(int u : g[v])
		if(!mark[u])
			dfs(u, g, nodes);
	nodes.push_back(v);
}

void scc(int n)
{
	vector <int> order;
	for(int i = 0; i < n; i++)
		if(!mark[i])
			dfs(i, g, order);
	fill(mark, mark + n, 0);
	fill(comp, comp + n, -1);
	for(; order.size(); order.pop_back())
	{
		int v = order.back();
		if(mark[v])
			continue;
		vector <int> nodes;
		dfs(v, h, nodes);
		for(int x : nodes)
			comp[x] = v;
	}
}
