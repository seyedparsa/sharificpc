struct GomoryHu
{
	int par[MAXN], ans[MAXN][MAXN]; // SET MAXIMUM NUMBER OF NODES
	int edges[4 * MAXE]; // SET MAXIMUM NUMBER OF EDGES
	int ecnt;
	void clear()
	{
		ecnt = 0;
	}
	void add_edge(int u, int v, int uv, int vu = 0)
	{
		edges[ecnt++] = u;
		edges[ecnt++] = v;
		edges[ecnt++] = uv;
		edges[ecnt++] = vu;
	}
	Flow graph; // USE flow.cpp
	void build(int n)
	{
		for (int i = 0; i < n; i++)
		{
			par[i] = 0;
			for (int j = 0; j < n; j++)
				ans[i][j] = 1e9; // SET YOUR INFINITY
		}
		for (int v = 1; v < n; v++)
		{
			graph.clear();
			for (int i = 0; i < ecnt; i += 4)
				graph.add_edge(edges[i], edges[i + 1], edges[i + 2], edges[i + 3]);
			int f = graph.max_flow(v, par[v]);
			for (int u = v + 1; u < n; u++)
				if (graph.d[u] != -1 && par[u] == par[v])
					par[u] = v;
			ans[v][par[v]] = ans[par[v]][v] = f;
			for (int u = 0; u < v; u++)
				ans[u][v] = ans[v][u] = min(f, ans[par[v]][u]);
		}
	}
	GomoryHu()
	{
		clear();
	}
};
