struct Delaunay{
    vector <pt> p;
    vector <int> to, nxt, perm;
    int add_edge(int q, int bef=-1){
        int cnt = sz(to);
        to.pb(q);
        nxt.pb(-1);
        if (bef != -1){
            nxt[bef] = cnt;
            to.pb(to[bef]);
            nxt.pb(-1);
        }
        return cnt;
    }
    bool onconvex(int e){
        if (nxt[nxt[nxt[e]]] != e) return true;
        if (dir(p[to[e^1]], p[to[e]], p[to[nxt[e]]]) < 0) return true;
        return false;
    }
    int before(int e){
        int cur = e, last = -1;
        do{
            last = cur;
            cur = nxt[cur^1];
        }while (cur != e);
        return last^1;
    }
    void easy_triangulate(){
        to.clear();
        nxt.clear();
        perm = vector<int>(sz(p));
        for (int i = 0; i < sz(p); i++)
            perm[i] = i;
        sort(perm.begin(), perm.end(), [&] (int i, int j){
            return p[i] < p[j]; });
        sort(p.begin(), p.end());
        if (dir(p[0], p[1], p[2]) > 0){
            swap(p[1], p[2]);
            swap(perm[1], perm[2]);
        }
        int to0 = add_edge(0), to0c = add_edge(2),
        to1 = add_edge(1), to1c = add_edge(0),
        to2 = add_edge(2), to2c = add_edge(1);
        nxt[to1] = to2; nxt[to2] = to0;
        nxt[to0] = to1; nxt[to0c] = to2c;
        nxt[to2c] = to1c; nxt[to1c] = to0c;
        int e = to0;
        bool D2 = true;
        for (int i = 3; i < sz(p); i++){
            pt q = p[i];
            if (D2){
                int edge = e;
                do{
                    if (dir(q, p[to[edge^1]], p[to[edge]])){
                        D2 = false;
                        break;
                    }
                    edge = nxt[edge];
                } while (edge != e);
            }
            vector <int> vis;
            if (D2){
                while (p[to[e^1]] < p[to[e]])
                    e = nxt[e];
                vis.pb(e);
                e = nxt[e];
            }
            else{
                while (dir(q, p[to[e^1]], p[to[e]]) <= 0 || dir(q, p[to[e^1]], p[to[before(e)^1]]) < 0)
                    e = nxt[e];
                while (dir(q, p[to[e^1]], p[to[e]]) > 0){
                    vis.pb(e);
                    e = nxt[e];
                }
            }
            int b = before(vis[0]);
            int ex = add_edge(i, b);
            int last = ex^1;
            for (int edge : vis){
                nxt[last] = edge;
                int eq = add_edge(i, edge);
                nxt[edge] = eq;
                nxt[eq] = last;
                last = eq^1;
            }
            nxt[ex] = last;
            nxt[last] = e;
        }
    }
    bool incircle(pt a, pt b, pt c, pt d){
        if (dir(a, b, c) < 0)
            swap(b, c);
        return a.z() * (b.x * (c.y - d.y) - c.x * (b.y - d.y)
                        + d.x * (b.y - c.y))
        - b.z() * (a.x * (c.y - d.y) - c.x  * (a.y - d.y) + d.x * (a.y - c.y))
        + c.z() * (a.x * (b.y - d.y) - b.x * (a.y - d.y) + d.x * (a.y - b.y))
        - d.z() * (a.x * (b.y - c.y) - b.x * (a.y - c.y) + c.x * (a.y - b.y)) > 0;
    }
    bool locally(int e){
        pt a = p[to[e^1]], b = p[to[e]], c = p[to[nxt[e]]], d = p[to[nxt[e^1]]];
        if (onconvex(e)) return true;
        if (onconvex(e^1)) return true;
        if (incircle(a, b, c, d)) return false;
        if (incircle(b, a, d, c)) return false;
        return true;
    }
    void flip(int e){
        int a = nxt[e], b = nxt[a],
        c = nxt[e^1], d = nxt[c];
        nxt[d] = a;
        nxt[b] = c;
        to[e] = to[c];
        nxt[a] = e;
        nxt[e] = d;
        to[e^1] = to[a];
        nxt[c] = e^1;
        nxt[e^1] = b;
    }
    void delaunay_triangulate(){
        if (sz(to) == 0)
            easy_triangulate();
        bool *mark = new bool[sz(to)];
        fill(mark, mark + sz(to), false);
        vector <int> bad;
        for (int e = 0; e < sz(to); e++){
            if (!mark[e/2] && !locally(e)){
                bad.pb(e);
                mark[e/2] = true;
            }
        }
        while (sz(bad)){
            int e = bad.back();
            bad.pop_back();
            mark[e/2] = false;
            if (!locally(e)){
                int to_check[4] = {nxt[e], nxt[nxt[e]], nxt[e^1], nxt[nxt[e^1]]};
                flip(e);
                for (int i = 0; i < 4; i++)
                    if (!mark[to_check[i]/2] && !locally(to_check[i])){
                        bad.pb(to_check[i]);
                        mark[to_check[i]/2] = true;
                    }
            }
        }
        for (int e = 0; e < sz(to); e++)
            assert(locally(e));
    }
    vector <tri> get_triangles(){
        vector <tri> res;
        bool *mark = new bool[sz(to)];
        fill(mark, mark + sz(to), false);
        for (int e = 0; e < sz(to); e++){
            if (mark[e]) continue;
            if (onconvex(e)) continue;
            pt a = p[to[e^1]], b = p[to[e]], c = p[to[nxt[e]]];
            mark[e] = mark[nxt[e]] = mark[nxt[nxt[e]]] = true;
            res.pb(tri(perm[to[e^1]], perm[to[e]], perm[to[nxt[e]]]));
        }
        return res;
    }
    vector <pair<ls, pt>> get_voronoi_edges(){
        vector <pair<ls, pt>> res;
        for (int e = 0; e < sz(to); e++){
            pt a = p[to[e^1]], b = p[to[e]], c = p[to[nxt[e]]], d = p[to[nxt[e^1]]];
            if (onconvex(e^1)){
                pt o1 = center(a, b, c),
                o2 = (a+b)/2;
                pt ab = (b-a);
                pt per(ab.y, -ab.x);
                o2 = o2 + per*100000; //infinity
                res.pb({{o1, o2}, a});
                continue;
            }
            if (onconvex(e)) continue;
            if (e&1) continue;
            res.pb({{center(a, b, c), center(b, a, d)}, a});
        }
        return res;
    }
    Delaunay(vector <pt> &p):p(p){}
};
