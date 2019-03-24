// be name khoda

#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <set>
#include <iostream>
#include <utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld eps=1e-8, INF = 1e12;

struct line{
       ll y0,m;
       line(){}
       line(ll t1,ll t2):y0(t1),m(t2){}
};
bool operator<(const line& l1,const line& l2){
       return (l1.m != l2.m ? l1.m<l2.m : l1.y0 < l2.y0);
}
set<line> s;
line last_line;
ld last_x;
void reset(){
       s.clear();
}
ld xinter(const line& l1,const line& l2){
       return ld(l1.y0-l2.y0)/ld(l2.m-l1.m);
}
ld yinter(const line& l1,ld x){
       return l1.m*x+l1.y0;
}
ld best(ld x){
       ld ans=-INF;
       set<line>::iterator it=s.find(last_line);
       while (it!=s.end() && yinter(*it,x)>ans){
               ans=yinter(*it,x);
               ++it;
       }
       --it;
       last_x=x;
       last_line=*it;
       return ans;
}
void insert(const line& l){
       while (true){
               set<line>::iterator it1=s.lower_bound(line(-INF, l.m));
               if (it1==s.end())
                       break;
               set<line>::iterator it2=it1;++it2;
               if (it2==s.end())
                       break;
               if (it1->m==l.m){
                       if (it1->y0<=l.y0){
                               s.erase(it1);
                               continue;
                       }
                       return;
               }
               ld x=xinter(*it1,*it2);
               if (yinter(l,x)<yinter(*it1,x)-eps)
                       break;
               s.erase(it1);
       }
       while (true){
               set<line>::iterator it1=s.upper_bound(line(-INF, l.m));
               if (it1==s.begin())
                       break;
               --it1;
               if (it1==s.begin())
                       break;
               set<line>::iterator it2=it1;--it2;
               if (it1->m==l.m){
                       if (it1->y0<=l.y0){
                               s.erase(it1);
                               continue;
                       }
                       return;
               }
               ld x=xinter(*it1,*it2);
               if (yinter(l,x)<yinter(*it1,x)-eps)
                       break;
               s.erase(it1);
       }
       set<line>::iterator it1=s.lower_bound(line(-INF, l.m));
       if (it1!=s.end() && it1!=s.begin()){
               set<line>::iterator it2=it1;--it2;
               ld x=xinter(*it1,*it2);
               if (yinter(l,x)<=yinter(*it1,x)+eps)
                       return;
       }
       s.insert(l);
       if (s.size()==1){
               last_line=l;
               last_x=-1e12;
       }
       else if (s.find(last_line)==s.end())
               last_line=l;
       else if (yinter(last_line,last_x)<yinter(l,last_x))
               last_line=l;
}

int main(){
	cerr << "Hello GP of moscow!" << endl;
}
