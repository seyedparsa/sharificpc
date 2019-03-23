const int N = 200002;
int comp[N], res[N];
vector <int> g[N], h[N];
bool mark[N];

void addE(int u, int v)
{
	g[u].push_back(v);
	h[v].push_back(u);
}

void addClause(int x, int y)
{
	addE(x ^ 1, y);
	addE(y ^ 1, x);
}

void dfs(int v, vector <int> *g, vector <int> &nodes)
{
	mark[v] = 1;
	for(int u : g[v])
		if(!mark[u])
			dfs(u, g, nodes);
	nodes.push_back(v);
}

bool check(int m)
{
	int n = m * 2;
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
		for(int x : nodes)
		{
			if(comp[x ^ 1] == comp[x])
				return false;
			res[x/2] = x % 2;
		}
	}
	return true;
}

