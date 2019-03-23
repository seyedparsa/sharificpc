
//be naame khodaa
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair <int, int> pii;
#define F first
#define S second
#define pb push_back

inline int in(){int x, y; y = scanf("%d", &x); return x;}

const int MN = 2e5 + 5;

vector<pii>Adj[MN];
int mh[MN] ,Cmp[MN] ,  h[MN] , es[MN] , ee[MN] ,cmp, n , m;
vector<int>st , C[MN], g[MN] , adj[MN];
bool mk[MN];
int H[MN] , V[MN], sz_v;

void DFS(int s,int pr,int Comp)
{
	Cmp[s] = Comp;
	mk[s] = true;
	mh[s] = h[s];

	for(auto x:Adj[s]){
		int v = x.first , e = x.second;
		if(mk[v]) continue;

		int lst = -1;
		if(!st.empty()) lst = st.back();
		
		h[v] = h[s]+1;
		DFS(v , e , Comp);

		if(mh[v] >= h[s]){
			
			while(!st.empty() && st.back() != lst){
				C[cmp].pb(st.back());
				st.pop_back();
			}
			++cmp;
		}

		mh[s] = min(mh[s] , mh[v]);
	}
	for(auto x:Adj[s]){
		int v = x.first , e = x.second;
		if(h[v] < h[s]){
			if(e ^ pr) mh[s] = min(mh[s] , h[v]);
			st.pb(e);
		}
	}
}

void init()
{
	cin >> n >> m;
	for(int i=0;i<m;++i){
		cin >> es[i] >> ee[i];
		--es[i] , --ee[i];
		Adj[es[i]].pb({ee[i] , i});
		Adj[ee[i]].pb({es[i] , i});
	}
	int counter = 0;
	for(int i=0;i<n;++i) if(!mk[i]) 
		DFS(i , -1 , counter++);

	for(int i=0;i<n;++i) Adj[i].clear();	
	memset(mk , 0 , sizeof mk);
	
	for(int i=0;i<cmp;++i){
		sz_v = 0;
		for(auto x:C[i])
			g[es[x]].pb(ee[x]) , g[ee[x]].pb(es[x]) ,
				V[sz_v++] = es[x] , V[sz_v++] = ee[x];
		
		sort(V , V+sz_v);
		sz_v = unique(V , V+sz_v) - V;
		
		for(int j=0;j<sz_v;++j){
			int v = V[j];
			adj[v].pb(i+n) , adj[i+n].pb(v);	
			mk[v] = false;
			g[v].clear();
		}

	}
	n += cmp;
}



int main(){
    return 0;
}
