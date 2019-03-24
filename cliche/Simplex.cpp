typedef vector <ld> vd;
typedef vector <int> vi;
const ld Eps = 1e-9;

vd simplex(vector <vd> a, vd b, vd c) {
	// ax = b, max(cTx)
	int n = a.size(), m = a[0].size() + 1, r = n, s = m - 1;
	vector <vd> d(n + 2, vd(m + 1, 0)); vd x(m - 1);
	vi ix(n + m); iota(ix.begin(), ix.end(), 0);
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < m - 1; j ++) d[i][j] = -a[i][j];
		d[i][m - 1] = 1;
		d[i][m] = b[i];
		if(d[r][m] > d[i][m]) 
			r = i;
	}

	for(int j = 0; j < m - 1; j ++) d[n][j] = c[j];
	d[n + 1][m - 1] = -1;

	while(true) {
		if(r < n) { 
			vd su;
			swap(ix[s], ix[r + m]); d[r][s] = 1 / d[r][s];
			for(int j = 0; j <= m; j ++) if(j != s) {
				d[r][j] *= -d[r][s]; if(d[r][j]) su.pb(j);
			}
			for(int i = 0; i <= n + 1; i ++) if(i != r) {
				for(int j = 0; j < su.size(); j ++)
					d[i][su[j]] += d[r][su[j]] * d[i][s];
				d[i][s] *= d[r][s];
			}
		} 
		r = s = -1;
		for(int j = 0; j < m; j ++) if(s < 0 || ix[s] > ix[j])
			if(d[n + 1][j] > Eps || d[n + 1][j] > -Eps &&
					d[n][j] > Eps) s = j; if(s < 0) break;
		for(int i = 0; i < n; i ++) if(d[i][s] < -Eps) {
			if(r < 0) { 
				r = i; 
				continue; 
			}
			double e = d[r][m] / d[r][s] - d[i][m] / d[i][s];
			if(e < -Eps || e < Eps && ix[r + m] > ix[i + m]) r = i;
		}
		if(r < 0) 
			return vd(); // Unbounded
	}

	if(d[n + 1][m] < -Eps) return vd(); // No solution

	for(int i = m; i < n + m; i ++)
		if(ix[i] < m - 1) x[ix[i]] = d[i - m][m];
	return x;
}
