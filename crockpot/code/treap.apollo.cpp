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
		long long pi_i_i;
		long long pi_i;
		long long pi;
		long long res;
		_Node *l, *r;

		_Node(T _x) {
			x = _x;
			y = ((rand() & ((1 << 16) - 1)) << 16) ^ rand();
			l = r = NULL;
			cnt = 1;
			pi_i_i = x.second;
			pi_i = x.second;
			pi = x.second;
		}
		~_Node() { delete l; delete r; }
		void recalc() {
			cnt = pi_i_i = pi_i = pi = 0;
			if (l)
			{
				cnt += l->cnt;
				pi_i_i += l->pi_i_i;
				pi_i += l->pi_i;
				pi += l->pi;
			}
			cnt++;
			pi_i_i += cnt * cnt * x.second;
			pi_i += cnt * x.second;
			pi += x.second;
			if (r)
			{
				pi_i_i += r->pi_i_i + r->pi * cnt * cnt + 2 * r->pi_i * cnt;
				pi_i += r->pi_i + r->pi * cnt;
				pi += r->pi;
				cnt += r->cnt;
			}
		}
		void debug() {
			if (l)
				l->debug();
			if (r)
				r->debug();
			cerr << x.first << " " << x.second << " " << (l ? l->x.first : -1) << " " << (r ? r->x.first : -1) << " " << cnt << " " << pi << " " << pi_i << " " << pi_i_i << endl;
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

vector<pii> v;

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		v.push_back(pii(x, -i));
	}

	int a, b;
	cin >> a >> b;
	sort(v.begin(), v.end(), greater<pii>());
	for (int i = 0; i < v.size(); i++)
	{
		t.insert(pii(-v[i].second, v[i].first));
		cout << (t.root->pi_i_i + t.root->pi_i * a + t.root->pi * b) << " ";
		//cerr << endl << "***" << endl;
		//t.root->debug();
		//cerr << endl << "***" << endl;
	}
	cout << endl;
}
