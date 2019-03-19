// Find a number X such that X%a[i]==r[i] for all (0<=i<n) (-1 if it's not exist) O(nlogn)
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
int n;
long long a[MAXN];
long long r[MAXN];

long long gcd(long long x,long long y,long long &c1,long long &c2) {
  if (y==0) {
    c1=1; c2=0;
    return x;
  }
  int r=x%y;
  long long ans=gcd(y,r,c2,c1);    
  c2-=c1*(x/y);
  return ans;
}
int solve_pair(long long &c,long long &rr,long long a,long long r) {
  long long c1=1,a1=1;
  long long g=gcd(c,a,c1,a1);
  long long c2=c/g,a2=a/g;
  long long rr1=rr%g,r1=r%g;
  if(rr1 != r1) return rr=-1;
  rr=(c2*(r/g)*c1+a2*a1*(rr/g))*g+rr1;

  c=c2*a2*g;
  rr=(rr%c+c)%c;
  return 0;
}
long long chinese_remainder() {
  long long c=a[0],rr=r[0];
  for(int i=1;i<n;i++){
    solve_pair(c,rr,a[i],r[i]);
    if(rr==-1)return -1;
  }
  return rr;
}
