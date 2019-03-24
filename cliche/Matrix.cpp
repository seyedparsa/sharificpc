const int MOD = 1e9 + 7;

struct Matrix
{
	ll **a;
	int n;
	Matrix(int n, int x = 0): n(n)
	{
		a = new ll*[n];
		for(int i = 0; i < n; i++)
		{
			a[i] = new ll[n];
			for(int j = 0; j < n; j++)
				a[i][j] = (i == j ? x : 0);
		}
	}
	ll *operator [](int x) { return a[x]; }
};

Matrix operator *(Matrix A, Matrix B)
{
	int n = A.n;
	Matrix C(n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			for(int k = 0; k < n; k++)
				C[i][j] = (C[i][j] + (A[i][k] * B[k][j]) % MOD) % MOD;
	return C;
}

Matrix operator ^(Matrix M, int t)
{
	Matrix Res(M.n, 1);
	for(; t > 0; t /= 2)
	{
		if(t % 2)
			Res = Res * M;
		M = M * M;
	}
	return Res;
}
