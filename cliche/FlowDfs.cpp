int from[MAXE], to[MAXE], cap[MAXE], prv[MAXE], head[MAXN], ec;

void addEdge(int u, int v, int uv, int vu = 0){
	from[ec] = u, to[ec] = v, cap[ec] = uv, prv[ec] = head[u], head[u] = ec++;
	from[ec] = v, to[ec] = u, cap[ec] = vu, prv[ec] = head[v], head[v] = ec++;
}

bool vis[MAXN];
int dfs(int v, int sink, int f = 1e9){
	if (v == sink) return f;
	if (vis[v]) return 0;
	vis[v] = true;
	for (int e = head[v]; ~e; e = prv[e])
		if (cap[e]){
			int x = dfs(to[e], sink, min(f, cap[e]));
			if (x){
				cap[e] -= x;
				cap[e^1] += x;
				return x;
			}
		}
	return 0;
}

int getMaxFlow(int source, int sink){
	int ret = 0, x;
	memset(vis, 0, sizeof(vis));
	while (x = dfs(source, sink)){
		ret += x;
		memset(vis, 0, sizeof(vis));
	}
	return ret;
}

int main(){
	memset(head, -1, sizeof(head));
	return 0;
}
