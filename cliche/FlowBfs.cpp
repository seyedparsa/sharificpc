int from[MAXE], to[MAXE], cap[MAXE], prv[MAXE], head[MAXN], ec;

void addEdge(int u, int v, int uv, int vu = 0){
	from[ec] = u, to[ec] = v, cap[ec] = uv, prv[ec] = head[u], head[u] = ec++;
	from[ec] = v, to[ec] = u, cap[ec] = vu, prv[ec] = head[v], head[v] = ec++;
}

int lv[MAXN], q[MAXN], rec[MAXN], parE[MAXN];
int bfs(int source, int sink) {
	memset(lv, 63, sizeof(lv));
	memset(parE, -1, sizeof(parE));
	memset(rec, 0, sizeof(rec));
	int h = 0, t = 0;
	lv[source] = 0;
	rec[source] = 1e9;
	q[t++] = source;
	while (t-h){
		int v = q[h++];
		for (int e = head[v]; ~e; e = prv[e])
			if (cap[e] && lv[v] + 1 < lv[to[e]]){
				lv[to[e]] = lv[v] + 1;
				parE[to[e]] = e;
				rec[to[e]] = min(cap[e], rec[v]);
				q[t++] = to[e];
			}
	}
	if (lv[sink] > 1e8) return 0;
	int v = sink;
	while (~parE[v]){
		int e = parE[v];
		cap[e] -= rec[sink];
		cap[e^1] += rec[sink];
		v = from[e];
	}
	return rec[sink];
}


int getMaxFlow(int source, int sink){
	int ret = 0, x;
	while (x = bfs(source, sink)) ret += x;
	return ret;
}

int main(){
	memset(head, -1, sizeof(head));
	return 0;
}
