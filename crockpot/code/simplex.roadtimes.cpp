#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 40;
const int INF = 1010 * MAXN;
const int MAXR = 110;
const int MAXE = 110;

typedef pair<int, int> pii;
typedef pair<pii, int> ppi;

#include <cmath>
#include <cstdio>
#include <memory.h>

const int MAXEQ = MAXR + MAXE;
const int MAXVAR = MAXE * 2 + MAXR;
const long double eps = 1e-8; // 1e-6?

struct Simplex {
	long double A[MAXEQ][MAXVAR+1];
	long double obj[MAXVAR+1];
	int ones[MAXEQ];

	long double saved[MAXVAR+1];
	long double sol[MAXVAR+1];

	int n_r, n_col;

	void mult_row(long double* row, long double k) {
		for (int j = 0; j <= n_col; j++)
			row[j] *= k;
	}
	void add_row_mult(long double* row_b, long double* row_a, long double mult) {
		for (int j = 0; j <= n_col; j++)
			row_b[j] += row_a[j]*mult;
	}
	void pivot(int r, int c) {
		mult_row(A[r], 1.0 / A[r][c]);
		ones[r] = c;
		for (int i = 0; i <= n_r; i++) {
			if (i != r && A[i][c] != 0)
				add_row_mult(A[i], A[r], -A[i][c]);
		}
		add_row_mult(obj, A[r], -obj[c]);
		add_row_mult(saved, A[r], -saved[c]);
	}
	void move_col(int c2, int c1) {
		for (int i = 0; i < n_r; i++)
		{ 
			A[i][c2] = A[i][c1]; 
			A[i][c1] = 0;
		}
		obj[c2] = obj[c1]; 
		obj[c1] = 0;
		saved[c2] = saved[c1]; 
		saved[c1] = 0;
	}

	long double solve_feasible() {
		while (true) {
			int new_one = -1;
			for (int j = 0; j < n_col; j++) 
				if (obj[j] < -eps) 
				{ 
					new_one = j; 
					break; 
				}
			if (new_one == -1) 
				break;

			int row = -1;
			long double lim = 1e100;
			for (int i = 0; i < n_r; i++) {
				if (A[i][new_one] > eps) {
					long double val = A[i][n_col] / A[i][new_one];
					if (val < lim) {
						lim = val;
						row = i;
					}
				}
			}
			if (row == -1) 
				return -1e100; // unbounded // !! promjena
			pivot(row, new_one);
		}
		memset(sol, 0, sizeof sol);
		for (int i = 0; i < n_r; i++) sol[ones[i]] = A[i][n_col];
		return obj[n_col];
	}

	bool get_feasibile() {
		int min_row = -1;
		for (int i = 0; i < n_r; i++) 
			if (min_row == -1 || A[i][n_col] < A[min_row][n_col]) 
				min_row = i;
		if (A[min_row][n_col] > eps) 
			return true; // basic feasible

		++n_col;
		for (int i = 0; i < n_col; i++) 
			saved[i] = obj[i];
		move_col(n_col, n_col-1);

		memset(obj, 0, sizeof obj);
		obj[n_col - 1] = 1;
		for (int i = 0; i < n_r; i++) 
			A[i][n_col - 1] = -1;

		pivot(min_row, n_col - 1);
		long double val = solve_feasible();
		if (val < -eps) 
			return false; // infeasible // !!!! promjena
		for (int i = 0; i < n_r; i++) {
			if (ones[i] == n_col - 1) {
				int maxj = -1;
				for (int j = 0; j < n_col; j++)
					if (maxj == -1 || fabs(A[i][j]) > fabs(A[i][maxj])) 
						maxj = j;
				pivot(i, maxj);
			}
		}

		move_col(n_col-1, n_col);
		for (int i = 0; i < n_col; i++)
			obj[i] = saved[i];
		--n_col;
		return true;
	}

	long double solve_all() {
		if (!get_feasibile()) return 1e100; // impossible
		return - solve_feasible(); // !!! promjena
	}
};

vector<ppi> edges;
int d[MAXN][MAXN];

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			cin >> d[i][j];
			if (d[i][j] == -1)
				d[i][j] = INF;
			else if (i != j)
				edges.push_back(ppi(pii(i, j), d[i][j]));
		}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)	
			for (int k = 0; k < n; k++)
				d[j][k] = min(d[j][k], d[j][i] + d[i][k]);

	static Simplex simplex;
	int r;
	cin >> r;
	simplex.n_col = edges.size() + edges.size() + r;
	simplex.n_r = r + edges.size();
	for (int i = 0; i < r; i++)
	{
		int s, dest, t;
		cin >> s >> dest >> t;
		for (int j = 0; j < edges.size(); j++)
		{
			int u = edges[j].first.first;
			int v = edges[j].first.second;
			int w = edges[j].second;
			if (d[s][u] + w + d[v][dest] == d[s][dest])
			{
				simplex.A[i][j] = w;
				t -= w;
			}
		}
		simplex.A[i][edges.size() + edges.size() + i] = 1;
		simplex.A[i][simplex.n_col] = t;
		simplex.obj[edges.size() + edges.size() + i] = 1;
		simplex.ones[i] = edges.size() + edges.size() + i;
		simplex.pivot(i, simplex.ones[i]);
	}
	for (int i = 0; i < edges.size(); i++)
	{
		simplex.A[r + i][i] = 1;
		simplex.A[r + i][edges.size() + i] = 1;
		simplex.ones[r + i] = edges.size() + i;
		simplex.A[r + i][simplex.n_col] = 1;
	}
	if (simplex.solve_all() > eps)
		throw "Impossible";
	int ptr = 0;
	for (int i = 0; i < simplex.n_r; i++)
	{
		if (simplex.ones[i] >= edges.size() + edges.size())
			for (int j = 0; j < edges.size() + edges.size(); j++)
				if (fabs(simplex.A[i][j]) > eps)
				{
					simplex.pivot(i, j);
					break;
				}
	}

	for (int i = 0; i < simplex.n_r; i++)
	{
		if (simplex.ones[i] < edges.size() + edges.size())
		{
			for (int j = 0; j < edges.size() + edges.size(); j++)
				simplex.A[ptr][j] = simplex.A[i][j];
			simplex.A[ptr][edges.size() + edges.size()] = simplex.A[i][edges.size() + edges.size() + r];
			simplex.ones[ptr] = simplex.ones[i];
			ptr++;
		}
	}


	simplex.n_r = ptr;
	simplex.n_col = edges.size() + edges.size();

	static Simplex simplex2;
	int q;
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		int s, t;
		cin >> s >> t;
		int res = 0;

		simplex2.n_r = simplex.n_r;
		simplex2.n_col = simplex.n_col;
		for (int j = 0; j < simplex.n_r; j++)
		{
			for (int k = 0; k <= simplex.n_col; k++)
				simplex2.A[j][k] = simplex.A[j][k];
			simplex2.ones[j] = simplex.ones[j];
		}
		for (int j = 0; j <= simplex.n_col; j++)
			simplex2.obj[j] = 0;
		for (int j = 0; j < edges.size(); j++)
		{
			int u = edges[j].first.first;
			int v = edges[j].first.second;
			int w = edges[j].second;
			if (d[s][u] + w + d[v][t] == d[s][t])
			{
				simplex2.obj[j] = w;
				res += w;
			}
		}
		for (int j = 0; j < simplex2.n_r; j++)
			simplex2.pivot(j, simplex2.ones[j]);
		long double mn = simplex2.solve_all();

		simplex2.n_r = simplex.n_r;
		simplex2.n_col = simplex.n_col;
		for (int j = 0; j < simplex.n_r; j++)
		{
			for (int k = 0; k <= simplex.n_col; k++)
				simplex2.A[j][k] = simplex.A[j][k];
			simplex2.ones[j] = simplex.ones[j];
		}
		for (int j = 0; j <= simplex.n_col; j++)
			simplex2.obj[j] = 0;
		for (int j = 0; j < edges.size(); j++)
		{
			int u = edges[j].first.first;
			int v = edges[j].first.second;
			int w = edges[j].second;
			if (d[s][u] + w + d[v][t] == d[s][t])
				simplex2.obj[j] = -w;
		}
		for (int j = 0; j < simplex2.n_r; j++)
			simplex2.pivot(j, simplex2.ones[j]);
		long double mx = -simplex2.solve_all();
		cout.precision(9);
		if (edges.size() == 0)
			cout << s << " " << t << " " << 0 << " " << 0 << endl;
		else
			cout << s << " " << t << " " << fixed << res + mn << " " << res + mx << endl;
	}
}



