#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

typedef long long ll;

const int MAXN = 3e5 + 10;
const ll INF = 1e14;

int n, m, k, tl[MAXN], tr[MAXN], s[MAXN], e[MAXN], mid[MAXN], ret[MAXN];
vector<int>	vec[MAXN], sec[MAXN];
ll nd[MAXN], w[MAXN], fen[MAXN];

ll get(int v){
	ll ret = 0;
	for (v++; v && ret < INF; v-=v&-v)
		ret += fen[v];
	return ret;
}

void add(int l, int r, ll val){
	for (l++; l < MAXN; l+=l&-l)	fen[l] += val;
	for (r++; r < MAXN; r+=r&-r)	fen[r] -= val;
}

void go(){
	memset(fen, 0, sizeof(fen));
	for (int i = 0; i <= k; i++)
		sec[i].clear();

	for (int i = 0; i < n; i++)
		if (s[i] <= e[i]){
			mid[i] = (s[i] + e[i])>>1;
			sec[mid[i]].push_back(i);
		}

	for (int i = 0; i < k; i++){
		if (tl[i] < tr[i])
			add(tl[i], tr[i], w[i]);
		else
			add(tl[i], m, w[i]), add(0, tr[i], w[i]);
	
		for (int j= 0; j < sec[i + 1].size(); j++){
			int v = sec[i + 1][j];
			ll sm = 0;
			for (int w = 0; sm < INF && w < vec[v].size(); w++)
				sm += get(vec[v][w]);
			if (sm >= nd[v])
				ret[v] = mid[v], e[v] = mid[v] - 1;
			else
				s[v] = mid[v] + 1;
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++){
		int p;	scanf("%d", &p), p--;
		vec[p].push_back(i);
	}
	for (int i = 0; i < n; i++)
		scanf("%lld", &nd[i]);
	scanf("%d", &k);
	for (int i = 0; i < k; i++)
		scanf("%d %d %lld", &tl[i], &tr[i], &w[i]), tl[i]--;

	for (int i = 0; i < n; i++)
		s[i] = 1, e[i] = k, ret[i] = k + 1;
	bool fl = 1;
	while (fl){
		go();

		fl = 0;
		for (int i = 0; !fl && i < n; i++)
			fl |= s[i] <= e[i];
	}
	
	for (int i = 0; i < n; i++)
		if (ret[i] == k + 1)
			printf("NIE\n");
		else
			printf("%d\n", ret[i]);
	return 0;
}
