const int N = 200002, E = 200002;

vector <int> g[N]; // In case of having multiple edges, g[i] is list of neighboring edges
vector <pair<int, int>> ces;
int up[N], h[N];
int from[E], to[E]; // Only if multiple edges exist
bool mark[N], iscv[N];

int cecvme(int v, int pare = -1) // With multiple edge
{
	up[v] = h[v];
	mark[v] = true;
	int children = 0;
	for(int e : g[v])
		if(e != pare)
		{
			int u = to[e] ^ from[e] ^ v;
			if(mark[u])
				up[v] = min(up[v], h[u]);
			else
			{
				h[u] = h[v] + 1;
				up[v] = min(up[v], cecvme(u, e));
				if(up[u] >= h[v] && pare != -1)
					iscv[v] = true;
				children++;
			}
		}
	if(pare != -1 && up[v] == h[v])
		ces.push_back({from[pare] ^ to[pare] ^ v, v}); // pare
	if(pare == -1 && children > 1)
		iscv[v] = true;
	return up[v];
}
 
int cecv(int v, int par = -1) // Without multiple edge
{
	up[v] = h[v];
	mark[v] = true;
	int children = 0;
	for(int u : g[v])
	{
		if(mark[u] && u != par)
			up[v] = min(up[v], h[u]);
		if(!mark[u])
		{
			h[u] = h[v] + 1;
			up[v] = min(up[v], cecv(u, v));
			if(up[u] >= h[v] && par != -1)
				iscv[v] = true;
			children++;
		}
	}
	if(par != -1 && up[v] == h[v])
		ces.push_back({par, v});
	if(par == -1 && children > 1)
		iscv[v] = true;
	return up[v];
}
