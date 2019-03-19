struct Flow
{
	int head[MAXN], q[MAXN], d[MAXN], ptr[MAXN]; // SET MAXIMUM NUMBER OF NODES
	int from[2 * MAXE], to[2 * MAXE], cap[2 * MAXE], prv[2 * MAXE]; // SET MAXIMUM NUMBER OF EDGES
	int ecnt;
	void clear()
	{
		memset(head, -1, sizeof(head));
		ecnt = 0;
	}
	void add_edge(int u, int v, int uv, int vu = 0)
	{
		from[ecnt] = u, to[ecnt] = v, cap[ecnt] = uv, prv[ecnt] = head[u]; head[u] = ecnt++;
		from[ecnt] = v, to[ecnt] = u, cap[ecnt] = vu, prv[ecnt] = head[v]; head[v] = ecnt++;
	}
	bool bfs(int source, int sink)
	{
		int h = 0, t = 0;
		memset(d, -1, sizeof(d));
		d[source] = 0;
		q[t++] = source;
		while (h < t)
		{
			int v = q[h++];
			for (int i = head[v]; i != -1; i = prv[i])
				if (cap[i] && d[to[i]] == -1)
				{
					d[to[i]] = d[v] + 1;
					q[t++] = to[i];
				}
		}
		return (d[sink] != -1);
	}
	int dfs(int v, int sink, int f = 1e9) // SET YOUR INFINITY
	{
		if (!f || v == sink)
			return f;
		int ans = 0;
		for (int &i = ptr[v]; i != -1; i = prv[i])
			if (d[to[i]] == d[v] + 1)
			{
				int x = dfs(to[i], sink, min(f, cap[i]));
				cap[i] -= x;
				cap[i ^ 1] += x;
				f -= x;
				ans += x;
				if (!f)
					break;
			}
		return ans;
	}
	int max_flow(int source, int sink)
	{
		int f = 0;
		while (bfs(source, sink))
		{
			int x;
			memcpy(ptr, head, sizeof(head));
			while (x = dfs(source, sink))
				f += x;
		}
		return f;
	}
	Flow()
	{
		clear();
	}
};
