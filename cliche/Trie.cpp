const int N = -1;
const int C = 30;

int tr[N][C], sz;

void insert(string t) {
	int cur = 0;
	for (char c:t) {
		int ch = c - 'a';
		if (!tr[cur][ch])
			tr[cur][ch] = ++sz;
		cur = tr[cur][ch];
	}
}
