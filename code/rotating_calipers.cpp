vector <pair<pt, pt>> get_antipodals(vector <pt> &p){
	int n = sz(p);
	sort(p.begin(), p.end());
	vector <pt> U, L;
	for (int i = 0; i < n; i++){
		while (sz(U) > 1 && side(U[sz(U)-2], U[sz(U)-1], p[i]) >= 0)
			U.pop_back();
		while (sz(L) > 1 && side(L[sz(L)-2], L[sz(L)-1], p[i]) <= 0)
			L.pop_back();
		U.pb(p[i]);
		L.pb(p[i]);
	}
	vector <pair<pt, pt>> res;
	int i = 0, j = sz(L)-1;
	while (i+1 < sz(U) || j > 0){
		res.pb({U[i], L[j]});
		if (i+1 == sz(U))   j--;
		else if (j == 0)    i++;
		else if (cross(L[j]-L[j-1], U[i+1]-U[i]) >= 0)  i++;
		else    j--;
	}
	return res;
}
