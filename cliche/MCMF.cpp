int from[MAXE], to[MAXE], cap[MAXE], ww[MAXE], prv[MAXE], head[MAXN], ec;

void addEdge(int u, int v, int uv, int w, int vu = 0){
	from[ec] = u, to[ec] = v, cap[ec] = uv, ww[ec] = w, prv[ec] = head[u], head[u] = ec++;
	from[ec] = v, to[ec] = u, cap[ec] = vu, ww[ec] = -w, prv[ec] = head[v], head[v] = ec++;
}

int lv[MAXN], q[MAXN], rec[MAXN], parE[MAXN];
bool mark[MAXN];
pii spfa(int source, int sink) {
	memset(lv, 63, sizeof(lv));
	memset(parE, -1, sizeof(parE));
	memset(rec, 0, sizeof(rec));
	memset(mark, 0, sizeof(mark));
	int h = 0, t = 0;
	lv[source] = 0;
	rec[source] = 1e9;
	q[t++] = source;
	mark[source] = true;
	while (t^h){
		int v = q[h++];
		if (h == MAXN) h = 0;
		mark[v] = false;
		for (int e = head[v]; ~e; e = prv[e])
			if (cap[e] && lv[v] + ww[e] < lv[to[e]]){
				lv[to[e]] = lv[v] + ww[e];
				parE[to[e]] = e;
				rec[to[e]] = min(cap[e], rec[v]);
				if (!mark[to[e]]){
					q[t++] = to[e];
					if (t == MAXN) t = 0;
					mark[to[e]] = true;
				}
			}
	}
	if (lv[sink] > 1e8) return {0, 0};
	int v = sink;
	int totW = 0;
	while (~parE[v]){
		int e = parE[v];
		cap[e] -= rec[sink];
		cap[e^1] += rec[sink];
		totW += ww[e] * rec[sink];
		v = from[e];
	}
	return {rec[sink], totW};
}

pii getMCMF(int source, int sink){
	pii ret(0, 0), x;
	while (true){
		x = spfa(source, sink);
		if (!x.F) break;
		ret.F += x.F;
		ret.S += x.S;
	}
	return ret;
}

int main(){
	memset(head, -1, sizeof(head));
	return 0;
}
