const int N = 2002;
const int INF = 1e9;
int hn, weight[N][N];
int x[N], y[N];
int hungarian()  // maximum weighted perfect matching{
	int n = hn;
	int p, q;
	vector<int> fx(n, -INF), fy(n, 0);
	fill(x, x + n, -1);
	fill(y, y + n, -1);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			fx[i] = max(fx[i], weight[i][j]);
	for (int i = 0; i < n; ) {
		vector<int> t(n, -1), s(n+1, i);
		for (p = 0, q = 1; p < q && x[i] < 0; ++p) {
			int k = s[p];
			for (int j = 0; j < n && x[i] < 0; ++j)
				if (fx[k] + fy[j] == weight[k][j] && t[j] < 0) {
					s[q++] = y[j], t[j] = k;
					if (y[j] < 0) // match found!
						for (int p = j; p >= 0; j = p)
							y[j] = k = t[j], p = x[k], x[k] = j;
				} 
		}
		if (x[i] < 0) {
			int d = INF;
			for (int k = 0; k < q; ++k)
				for (int j = 0; j < n; ++j)
					if (t[j] < 0) d = min(d, fx [s[k]] + fy[j] - weight[s[k]][j]);
			for (int j = 0; j < n; ++j) fy[j] += (t[j] < 0? 0: d);
			for (int k = 0; k < q; ++k) fx[s[k]] -= d;
		} else ++i;
	}
	int ret = 0;
	for (int i = 0; i < n; ++i) ret += weight[i][x[i]];
	return ret;
} 
