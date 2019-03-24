const int N = 1000*1000 + 5;

int fen[N];

void add(int x, int val){
	for (++x; x < N; x += x&-x)
		fen[x] += val;
}

int get(int x){
	int res = 0;
	for (; x > 0; x -= x&-x)
		res += fen[x];
	return res;
}

int get(int l, int r){ return get(r) - get(l); }

