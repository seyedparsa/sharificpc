struct point{
  int X,Y,Z;
  point(int x=0,int y=0,int z=0){
    X=x; Y=y; Z=z;
  }
  bool operator==(const point& rhs) const {
    return (rhs.X==this->X && rhs.Y==this->Y && rhs.Z==this->Z);
  }
  bool operator<(const point& rhs) const {
    return rhs.X > this->X || (rhs.X == this->X && rhs.Y > this->Y) || (rhs.X==this->X && rhs.Y==this->Y && rhs.Z>this->Z);
  }
};
  
const int maxn=1000;
int n;
point P[maxn];
vector<point>ans;
queue<pii>Q;
set<pii>mark;
int cross2d(point p,point q){ return p.X*q.Y-p.Y*q.X;}
point operator -(point p,point q){ return point(p.X-q.X,p.Y-q.Y,p.Z-q.Z); }
point _cross(point u,point v){ return point(u.Y*v.Z-u.Z*v.Y,u.Z*v.X-u.X*v.Z,u.X*v.Y-u.Y*v.X); }
point cross(point o,point p,point q){ return _cross(p-o,q-o);}
point shift(point p) { return point(p.Y,p.Z,p.X);}
point norm(point p)
{
  if(p.Y<p.X || p.Z<p.X) p=shift(p);
  if(p.Y<p.X) p=shift(p);
  return p;
}

int main()
{
  cin>>n;
  int mn=0;
  for(int i=0;i<n;i++){
    cin>>P[i].X>>P[i].Y>>P[i].Z;
    if(P[i]<P[mn]) mn=i;
  }
  int nx=(mn==0);
  for(int i=0;i<n;i++)
    if(i!=mn && i!=nx && cross2d(P[nx]-P[mn],P[i]-P[mn])>0)
      nx=i;
  Q.push(pii(mn,nx));
  while(!Q.empty())
    {
      int v=Q.front().first,u=Q.front().second;
      Q.pop();
      if(mark.find(pii(v,u))!=mark.end()) continue;
      mark.insert(pii(v,u));
      int p=-1;
      for(int q=0;q<n;q++)
	if(q!=v && q!=u)
	  if(p==-1 || dot(cross(P[v],P[u],P[p]),P[q]-P[v])<0)
	    p=q;
      ans.push_back(norm(point(v,u,p)));
      Q.push(pii(p,u));
      Q.push(pii(v,p));
    }
  sort(ans.begin(),ans.end());
  ans.resize(unique(ans.begin(),ans.end())-ans.begin());
  for(int i=0;i<ans.size();i++)
    cout<<ans[i].X<<" "<<ans[i].Y<<" "<<ans[i].Z<<endl;
}
