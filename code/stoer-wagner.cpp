const int N = -1, MAXW = -1;
int g[N][N], v[N], w[N], na[N];
bool a[N];
int minCut( int n ) // initialize g[][] before calling!{
    for( int i = 0; i < n; i++ ) v[i] = i;
    int best = MAXW * n * n;
    while( n > 1 ){
        // initialize the set A and vertex weights
        a[v[0]] = true;
        for( int i = 1; i < n; i++ ){
            a[v[i]] = false;
            na[i - 1] = i;
            w[i] = g[v[0]][v[i]];
        }
        // add the other vertices
        int prev = v[0];
        for( int i = 1; i < n; i++ ){
            // find the most tightly connected non-A vertex
            int zj = -1;
            for( int j = 1; j < n; j++ )
                if( !a[v[j]] && ( zj < 0 || w[j] > w[zj] ) )
                    zj = j;
            // add it to A
            a[v[zj]] = true;
            // last vertex?
            if( i == n - 1 ){
                // remember the cut weight
                best = min(best, w[zj]);

                // merge prev and v[zj]
                for( int j = 0; j < n; j++ )
                    g[v[j]][prev] = g[prev][v[j]] += g[v[zj]][v[j]];
                v[zj] = v[--n];
                break;
            }
            prev = v[zj];
            // update the weights of its neighbors
            for( int j = 1; j < n; j++ ) if( !a[v[j]] )
                w[j] += g[v[zj]][v[j]];
        }
    }
    return best;
}
