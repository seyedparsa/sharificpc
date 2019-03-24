struct Base
{
    int a[B] = {};
    int eliminate(int x)
    {
        for(int i=B-1; i>=0; --i) if((1<<i)&x) x ^= a[i];
        return x;
    }
    void add(int x)
    {
        x = eliminate(x);
        for(int i=B-1; i>=0; --i) if((1<<i)&x)
        {
            a[i] = x;
            return;
        }
    }
    int size()
    {
        int cnt = 0;
        for(int i=0; i<B; ++i) if(a[i]) ++cnt;
        return cnt;
    }
};
