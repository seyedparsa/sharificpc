const int N = 1000*100 + 10;
struct point { 
    ll x, y, z; 
};
typedef vector<point> circle;
bool ccw(point a, point b, point c) { 
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y) >= 0;
}
bool incircle( circle a , point p ) {
    if( sz(a) == 0 ) return false;
    if( sz(a) == 1 ) 
        return a[0].x == p.x && a[0].y == p.y; 
    if( sz(a) == 2 ) {
        point mid = {a[0].x+a[1].x, a[0].y+a[1].y}; 
        return sq(2*p.x-mid.x) + sq( 2*p.y-mid.y) <= sq(2*a[0].x-mid.x) + sq(2*a[0].y-mid.y);
    }
    if( !ccw(a[0], a[1], a[2]) )
        swap(a[0], a[2]);
    return incircle(a[0],a[1],a[2], p) >= 0;
}
point a[N];
circle solve(int i, circle curr) { 
    assert(curr.size() <= 3);
    if( i == 0 ) 
        return curr;
    circle ret = solve(i-1, curr);
    if( incircle(ret, a[i-1]) ) 
        return ret; 
    curr.pb(a[i-1]);
    return solve(i-1, curr); 
}
int n;
void gg(circle c) { 
    if( sz(c) == 1 ) {
        cout << ld(a[0].x) << " " << ld(a[0].y) << endl;
        cout << 0.l << endl;
        return;
    }
    if( sz(c) == 2 ) { 
        point mid = {c[0].x+c[1].x, c[0].y+c[1].y}; 
        ld ret = sqrt(sq(2*c[0].x-mid.x) + sq(2*c[0].y-mid.y))/2;
        cout << ld(mid.x) / 2 << " " << ld(mid.y) /2 << endl;
        cout << ret << endl;
    } else { 
        lpt a[3]; 
        for(int i = 0; i < 3; i++) 
            a[i] = lpt(c[i].x, c[i].y); 
        lpt A = ld(0.5) * (a[0] + a[1]), C = ld(0.5) * (a[1] + a[2]);
        lpt B = A + (a[1] - a[0]) * lpt(0, 1), D = C + (a[2] - a[1]) * lpt(0, 1); 
        lpt center = intersection( A , B , C , D ); 
        ld ret = abs(a[0] - center);
        cout << center.real() << " " << center.imag() << endl;
        cout << ret << endl;
    }
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].z = sq(a[i].x) + sq(a[i].y); 
    }
    srand(time(NULL));
    for(int i = 1; i < n; i++) 
        swap(a[i], a[rand()%(i+1)]);
    circle ans = solve(n, circle());
    cout << fixed << setprecision(3) ;
    gg(ans);
    return 0;
}
