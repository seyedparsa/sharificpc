#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

struct Treap {
	typedef pii T;
	typedef struct _Node {
		T x;
		int y, cnt;
		_Node *l, *r;

		_Node(T _x) {
			x = _x;
			y = ((rand() & ((1 << 16) - 1)) << 16) ^ rand();
			l = r = NULL;
			cnt = 1;
		}
		~_Node() { delete l; delete r; }
		void recalc() {
			cnt = 0;
			if (l)
				cnt += l->cnt;
			cnt++;
			if (r)
				cnt += r->cnt;
		}
		void debug() {
			if (l)
				l->debug();
			if (r)
				r->debug();
			cerr << x.first << " " << x.second << " " << (l ? l->x.first : -1) << " " << (r ? r->x.first : -1) << " " << cnt << endl;
		}
	} *Node;

	Node merge(Node l, Node r) {
		if (!l || !r) return l ? l : r;
		if (l->y < r->y) {
			l->r = merge(l->r, r);
			l->recalc();
			return l;
		} else {
			r->l = merge(l, r->l);
			r->recalc();
			return r;
		}
	}

	void split(Node v, T x, Node &l, Node &r, bool eq=false) {
		l = r = NULL;
		if (!v) return;
		if (v->x < x || (eq && v->x == x)) {
			split(v->r, x, v->r, r);
			l = v;
		} else {
			split(v->l, x, l, v->l);
			r = v;
		}
		v->recalc();
	}

	Node root;
	Treap() : root(NULL) {}
	~Treap() { delete root; }
	void insert(T x) {
		Node l, r;
		split(root, x, l, r);
		root = merge(merge(l, new _Node(x)), r);
	}
	void erase(T x) {
		Node l, m, r;
		split(root, x, l, m);
		split(m, x, m, r, true);
		// assert(m && m->cnt == 1 && m->x == x);
		delete m;
		root = merge(l, r);
	}
	int size() const { return root ? root->cnt : 0; }
};

Treap t;

