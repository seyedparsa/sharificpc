/*
	GETS:
		call make_graph(n) at first
		you should use add_edge(u,v,w) and
		add pair of vertices as edges (vertices are 0..n-1)
	GIVES:
		output of dmst(v) is the minimum arborescence with root v in directed graph
		(INF if it hasn't a spanning arborescence with root v)
	O(mlogn)
*/
const int INF = 2e7;
struct MinimumAborescense{
	struct edge { 
		int src, dst, weight;
	};
	struct union_find {
		vector<int> p; 
		union_find(int n) : p(n, -1) { };
		bool unite(int u, int v) { 
			if ((u = root(u)) == (v = root(v))) return false;
			if (p[u] > p[v]) swap(u, v);
			p[u] += p[v]; p[v] = u;
			return true;
		}
		bool find(int u, int v) { return root(u) == root(v); }
		int root(int u) { return p[u] < 0 ? u : p[u] = root(p[u]); }
		int size(int u) { return -p[root(u)]; }
	};
	struct skew_heap {
		struct node {
			node *ch[2];
			edge key;
			int delta;
		} *root;
		skew_heap() : root(0) { }
		void propagate(node *a) {
			a->key.weight += a->delta;
			if (a->ch[0]) a->ch[0]->delta += a->delta;
			if (a->ch[1]) a->ch[1]->delta += a->delta;
			a->delta = 0;
		}
		node *merge(node *a, node *b) {
			if (!a || !b) return a ? a : b;
			propagate(a); propagate(b);
			if (a->key.weight > b->key.weight) swap(a, b);
			a->ch[1] = merge(b, a->ch[1]);
			swap(a->ch[0], a->ch[1]);
			return a;
		}
		void push(edge key) {
			node *n = new node();
			n->ch[0] = n->ch[1] = 0;
			n->key = key; n->delta = 0;
			root = merge(root, n);
		}
		void pop() {
			propagate(root);
			node *temp = root;
			root = merge(root->ch[0], root->ch[1]);
		}
		edge top() {
			propagate(root);
			return root->key;
		}
		bool empty() { 
			return !root;
		}
		void add(int delta) {
			root->delta += delta;
		}
		void merge(skew_heap x) {
			root = merge(root, x.root);
		}
	};
	vector<edge> edges;
	void add_edge(int src, int dst, int weight) {
		edges.push_back({src, dst, weight});
	}
	int n;
	void make_graph(int _n) {
		n = _n;
		edges.clear();
	}
	int dmst(int r) {
		union_find uf(n);
		vector<skew_heap> heap(n);
		for (auto e: edges) 
			heap[e.dst].push(e);
		double score = 0;
		vector<int> seen(n, -1);
		seen[r] = r;
		for (int s = 0; s < n; ++s) {
			vector<int> path;
			for (int u = s; seen[u] < 0;) {
				path.push_back(u);
				seen[u] = s;
				if (heap[u].empty()) return INF;
				edge min_e = heap[u].top(); 
				score += min_e.weight;
				heap[u].add(-min_e.weight);
				heap[u].pop();
				int v = uf.root(min_e.src);
				if (seen[v] == s) {
					skew_heap new_heap;
					while (1) {
						int w = path.back();
						path.pop_back();
						new_heap.merge(heap[w]);
						if (!uf.unite(v, w)) break;
					}
					heap[uf.root(v)] = new_heap;
					seen[uf.root(v)] = -1;
				}
				u = uf.root(v);
			}
		}
		return score;
	}
};
