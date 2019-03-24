const int N = 101, INF = 1e9 + 1;

int d[N][N];

int main()
{
	int n = in();
	for(int i = 0; i < n; i++)
	{
		fill(d[i], d[i] + n, INF);
		d[i][i] = 0;
	}
	for(int m = in(); m; m--)
	{
		int u = in() - 1, v = in() - 1;
		d[u][v] = d[v][u] = min(d[u][v], in());
	}
	for(int k = 0; k < n; k++)
		for(int u = 0; u < n; u++)
			for(int v = 0; v < n; v++)
				d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
}
