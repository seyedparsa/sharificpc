#include <cmath>
#include <cstdio>
#include <memory.h>

const int MAXEQ = 310;
const int MAXVAR = 310;
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
