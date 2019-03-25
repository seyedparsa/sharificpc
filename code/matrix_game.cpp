ld solve(int n, int m){    
    VVD A;
    VD B;
    VD C;
    for (int j = 0; j < m; j++){
        VD v;
        for (int i = 0; i < n; i++)
            v.pb(-mat[i][j]);
        v.pb(1);
        A.pb(v);
    }
    VD v;
    for (int i = 0; i < n; i++)
        v.pb(1);
    v.pb(0);
    A.pb(v);
    v.clear();
    for (int i = 0; i < n; i++)
        v.pb(-1);
    v.pb(0);
    A.pb(v);
    for (int i = 0; i < m; i++)
        B.pb(0);
    B.pb(1);
    B.pb(-1);
    for (int i = 0; i < n; i++)
        C.pb(0);
    C.pb(1);
    LPSolver solver(A, B, C);
    VD x;
    ld res = solver.Solve(x);
    return res;
}
