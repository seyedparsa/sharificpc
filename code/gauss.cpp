const int N = 505, MOD = 1e9 + 7;
typedef vector <ll> vec;
ll pw(ll a, ll b) {
	if(!b)
		return 1;
	ll x = pw(a, b/2);
	return x * x % MOD * (b % 2 ? a : 1) % MOD;
}
ll inv(ll x) { return pw(x, MOD - 2); }
bool solve() {
	int n = in();
	vector <vec> matrix(n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			matrix[i].push_back((in() % MOD + MOD) % MOD);
		}
	ll res = 1;
	for(int i = 0; i < n; i++) {
		int ind = -1;
		for(int row = i; row < n; row++)
			if(matrix[row][i])
				ind = row;
		if(ind == -1) {
			res = 0;
			break;
		}
		if(i != ind)
			res = (MOD - res)%MOD;
		matrix[i].swap(matrix[ind]);
		res = res * matrix[i][i] % MOD;
		ll inverse = inv(matrix[i][i]);
		for(int row = i + 1; row < n; row++) {
			ll z = matrix[row][i] * inverse % MOD;
			for(int j = 0; j < n; j++)
				matrix[row][j] = (matrix[row][j] % MOD - matrix[i][j]*z % MOD + MOD) % MOD;
		}
	}
	cout << res << endl;
}
