/*
	GETS:
		call make_graph(n) at first
		you should use add_edge(u,v,w) and
		add pair of vertices as edges (vertices are 0..n-1)
	GIVES:
		output of dmst(v) is the minimum arborescence with root v in directed graph
		(-1 if it hasn't a spanning arborescence with root v)
	O(mn)
*/
const int INF = 2e7;
struct MinimumAborescense{
	int n;
	struct edge {
		int src, dst;
		int weight;
	};
	vector<edge> edges;
	void make_graph(int _n) {
		n=_n;
		edges.clear();
	}
	void add_edge(int u, int v, int w) {
		edges.push_back({u, v, w});
	}
	int dmst(int r) {
		int N = n;
		for (int res = 0; ;) {
			vector<edge> in(N, {-1,-1,(int)INF});
			vector<int> C(N, -1);
			for (auto e: edges)
				if (in[e.dst].weight > e.weight) 
					in[e.dst] = e;
			in[r] = {r, r, 0};

			for (int u = 0; u < N; ++u) { // no comming edge ==> no aborescense
				if (in[u].src < 0) return -1;
				res += in[u].weight;
			}
			vector<int> mark(N, -1); // contract cycles
			int index = 0;
			for (int i = 0; i < N; ++i) {
				if (mark[i] != -1) continue;
				int u = i;
				while (mark[u] == -1) {
					mark[u] = i;
					u = in[u].src;
				}
				if (mark[u] != i || u == r) continue;
				for (int v = in[u].src; u != v; v = in[v].src) C[v] = index;
				C[u] = index++;
			}
			if (index == 0) return res; // found arborescence
			for (int i = 0; i < N; ++i) // contract
				if (C[i] == -1) C[i] = index++;

			vector<edge> next;
			for (auto &e: edges) 
				if (C[e.src] != C[e.dst] && C[e.dst] != C[r]) 
					next.push_back({C[e.src], C[e.dst], e.weight - in[e.dst].weight});
			edges.swap(next);
			N = index; r = C[r];
		}
	}
};
