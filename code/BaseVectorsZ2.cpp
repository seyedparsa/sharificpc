struct Base{
    ll a[B] = {};
    ll eliminate(ll x){
        for(int i=B-1; i>=0; --i) if(x >> i & 1) x ^= a[i];
        return x;
    }
    void add(ll x){
        x = eliminate(x);
        for(int i=B-1; i>=0; --i) if(x >> i & 1)
        {
            a[i] = x;
			for(int j = i - 1; j >= 0; j--) if(a[j] >> i & 1) a[j] ^= x;
            return;
        }
    }
    int size(){
        int cnt = 0;
        for(int i=0; i<B; ++i) if(a[i]) ++cnt;
        return cnt;
    }
};
