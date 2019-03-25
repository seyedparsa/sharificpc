int from[MAXE], to[MAXE], cap[MAXE], prv[MAXE], head[MAXN], pt[MAXN], ec;
void addEdge(int u, int v, int uv, int vu = 0){
	from[ec] = u, to[ec] = v, cap[ec] = uv, prv[ec] = head[u], head[u] = ec++;
	from[ec] = v, to[ec] = u, cap[ec] = vu, prv[ec] = head[v], head[v] = ec++;
}
int lv[MAXN], q[MAXN];
bool bfs(int source, int sink){
	memset(lv, 63, sizeof(lv));
	int h = 0, t = 0;
	lv[source] = 0;
	q[t++] = source;
	while (t-h){
		int v = q[h++];
		for (int e = head[v]; ~e; e = prv[e])
			if (cap[e] && lv[v] + 1 < lv[to[e]]){
				lv[to[e]] = lv[v] + 1;
				q[t++] = to[e];
			}
	}
	return lv[sink] < 1e8;
}
int dfs(int v, int sink, int f = 1e9){
	if (v == sink || f == 0)
		return f;
	int ret = 0;
	for (int &e = pt[v]; ~e; e = prv[e])
		if (lv[v]+1 == lv[to[e]]){
			int x = dfs(to[e], sink, min(f, cap[e]));
			cap[e] -= x;
			cap[e^1] += x;
			ret += x;
			f -= x;
			if (!f)
				break;
		}
	return ret;
}
int dinic(int source, int sink){
	int ret = 0;
	while (bfs(source, sink)){
		memcpy(pt, head, sizeof(head));
		ret += dfs(source, sink);
	}
	return ret;
}
