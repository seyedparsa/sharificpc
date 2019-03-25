const int N = 2000*100 + 10;
const int L = 20; 
int par[N][L], h[N], fath[N], st[N], en[N], sz[N]; 
vector<int> c[N]; //Adjacency List
int dsz(int s, int p) { 
    sz[s] = 1; 
    for(int xt = 0; xt < sz(c[s]); xt++) { 
        int x = c[s][xt]; 
        if( x != p ) { 
            sz[s] += dsz( x , s ); 	
            if( sz[x] > sz[c[s][0]] ) 
                swap( c[s][0], c[s][xt] ); 
        }
    }
    return sz[s]; 
}
void dfs(int s, int p) { 
    static int ind = 0;
    st[s] = ind++;
    for(int k = 1; k < L; k++) 
        par[s][k] = par[par[s][k-1]][k-1];
    for(int xt = 0; xt < sz(c[s]); xt++) { 
        int x = c[s][xt]; 
        if( x == p ) continue; 
        fath[x] = x;
        if( xt == 0 ) fath[x] = fath[s]; 
        h[x] = h[s] + 1; 
        par[x][0] = s;
        dfs(x, s); 
    }
    en[s] = ind; 
}
int n, q;
void upset(int u, int w, int qv) { 
    int stL = max( st[w] , st[fath[u]] ); 
    set( stL, st[u] + 1 , qv , 0, n , 1 ); 
    if( stL == st[w] ) return; 
    upset( par[fath[u]][0] , w , qv ); 
}
