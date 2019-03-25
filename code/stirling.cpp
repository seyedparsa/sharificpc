const int mod = 998244353;
const int root = 15311432;
const int root_1 = 469870224;
const int root_pw = 1 << 23;
const int N = 400004;
vector<int> v[N];
ll modInv(ll a, ll mod = mod){
	ll x0 = 0, x1 = 1, r0 = mod, r1 = a;
	while(r1){
		ll q = r0 / r1;
		x0 -= q * x1; swap(x0, x1);
		r0 -= q * r1; swap(r0, r1);
	}
	return x0 < 0 ? x0 + mod : x0;
}
void fft (vector<int> &a, bool inv) {
	int n = (int) a.size();
	for (int i=1, j=0; i<n; ++i) {
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}
	for (int len=2; len<=n; len<<=1) {
		int wlen = inv ? root_1 : root;
		for (int i=len; i<root_pw; i<<=1)
			wlen = int (wlen * 1ll * wlen % mod);
		for (int i=0; i<n; i+=len) {
			int w = 1;
			for (int j=0; j<len/2; ++j) {
				int u = a[i+j],  v = int (a[i+j+len/2] * 1ll * w % mod);
				a[i+j] = u+v < mod ? u+v : u+v-mod;
				a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
				w = int (w * 1ll * wlen % mod);
			}
		}
	}
	if(inv) {
		int nrev = modInv(n, mod);
		for (int i=0; i<n; ++i)
			a[i] = int (a[i] * 1ll * nrev % mod);
	}
}
void pro(const vector<int> &a, const vector<int> &b, vector<int> &res) {
	vector<int> fa(a.begin(), a.end()),  fb(b.begin(), b.end());
	int n = 1;
	while (n < (int) max(a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);

	fft(fa, false), fft (fb, false);
	for (int i = 0; i < n; ++i)
		fa[i] = 1LL * fa[i] * fb[i] % mod;
	fft (fa, true);
	res = fa;
}
int S(int n, int r) {
	int nn = 1;
	while(nn < n) nn <<= 1;
	for(int i = 0; i < n; ++i) {
		v[i].push_back(i);
		v[i].push_back(1);
	}
	for(int i = n; i < nn; ++i) {
		v[i].push_back(1);
	}
	for(int j = nn; j > 1; j >>= 1){
		int hn = j >> 1;
		for(int i = 0; i < hn; ++i){
			pro(v[i], v[i + hn], v[i]);
		}
	}
	return v[0][r];
}

int fac[N], ifac[N], inv[N];

void prencr(){
	fac[0] = ifac[0] = inv[1] = 1;
	for(int i = 2; i < N; ++i)
		inv[i] = mod - 1LL * (mod / i) * inv[mod % i] % mod;
	for(int i = 1; i < N; ++i){
		fac[i] = 1LL * i * fac[i - 1] % mod;
		ifac[i] = 1LL * inv[i] * ifac[i - 1] % mod;
	}
}

int C(int n, int r){
	return (r >= 0 && n >= r) ? (1LL * fac[n] * ifac[n - r] % mod * ifac[r] % mod) : 0;
}

int main(){
	prencr();
	int n, p, q;
	cin >> n >> p >> q;
	ll ans = C(p + q - 2, p - 1);
	ans *= S(n - 1, p + q - 2);
	ans %= mod;
	cout << ans;
}
