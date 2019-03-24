const int N = -1, E = -1, INF = 1e9 + 1;

int from[E], to[E], w[E], dist[N];

int main()
{
	int n = in(), m = in();
	for(int i = 0; i < m; i++)
	{
		from[i] = in() - 1;
		to[i] = in() - 1;
		w[i] = in();
	}
	fill(dist, dist + n, INF);
	dist[st] = 0;
	for(int i = 0; i < n - 1; i++)
		for(int e = 0; e < m; e++)
			d[to[e]] = min(d[to[e]], d[from[e]] + w[e]);
}
