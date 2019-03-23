const int MOD = 1e9 + 7;

ll rpw(ll a, ll b){
	if(b == 0)
		return 1;
	ll m = b/2;
	ll x = rpw(a, b/2);
	x = x * x % MOD;
	if(b % 2)
		x = x * a % MOD;
	return x;
}

ll pw(ll a, ll b){
	ll ret = 1;
	while (b){
		if (b & 1)
			ret = ret*a%MOD;
		b >>= 1;
		a = a*a%MOD;
	}
	return ret;
}
