/*
GETS:
n->number of vertices
you should use add_edge(u,v) and
add pair of vertices as edges (vertices are 0..n-1)
(note: please don't add multiple edge)
GIVES:
output of edmonds() is the maximum matching in general graph
match[i] is matched pair of i (-1 if there isn't a matched pair)
O(mn^2)
*/
struct struct_edge{int v;struct_edge* nxt;};
typedef struct_edge* edge;
const int MAXN=500;
struct Edmonds{
	struct_edge pool[MAXN*MAXN*2];
	edge top=pool,adj[MAXN];
	int n,match[MAXN],qh,qt,q[MAXN],father[MAXN],base[MAXN];
	bool inq[MAXN],inb[MAXN];
	void add_edge(int u,int v){
		top->v=v,top->nxt=adj[u],adj[u]=top++;
		top->v=u,top->nxt=adj[v],adj[v]=top++;
	}
	int LCA(int root,int u,int v){
		static bool inp[MAXN];
		memset(inp,0,sizeof(inp));
		while(1){
			inp[u=base[u]]=true;
			if (u==root) break;
			u=father[match[u]];
		}
		while(1){
			if (inp[v=base[v]]) return v;
			else v=father[match[v]];
		}
	}
	void mark_blossom(int lca,int u){
		while (base[u]!=lca){
			int v=match[u];
			inb[base[u]]=inb[base[v]]=true;
			u=father[v];
			if (base[u]!=lca) father[u]=v;
		}
	}
	void blossom_contraction(int s,int u,int v){
		int lca=LCA(s,u,v);
		memset(inb,0,sizeof(inb));
		mark_blossom(lca,u);
		mark_blossom(lca,v);
		if (base[u]!=lca)
			father[u]=v;
		if (base[v]!=lca)
			father[v]=u;
		for (int u=0;u<n;u++)
			if (inb[base[u]]){
				base[u]=lca;
				if (!inq[u])
					inq[q[++qt]=u]=true;
			}
	}
	int find_augmenting_path(int s){
		memset(inq,0,sizeof(inq));
		memset(father,-1,sizeof(father));
		for (int i=0;i<n;i++) base[i]=i;
		inq[q[qh=qt=0]=s]=true;
		while (qh<=qt){
			int u=q[qh++];
			for (edge e=adj[u];e;e=e->nxt){
				int v=e->v;
				if (base[u]!=base[v] && match[u]!=v){
					if (v==s || (match[v]!=-1 && father[match[v]]!=-1))
						blossom_contraction(s,u,v);
					else if (father[v]==-1){
						father[v]=u;
						if (match[v]==-1)
							return v;
						else if (!inq[match[v]])
							inq[q[++qt]=match[v]]=true;
					}
				}
			}
		}
		return -1;
	}
	int augment_path(int s,int t){
		int u=t,v,w;
		while (u!=-1){
			v=father[u];
			w=match[v];
			match[v]=u;
			match[u]=v;
			u=w;
		}
		return t!=-1;
	}
	int edmonds(){
		int matchc=0;
		memset(match,-1,sizeof(match));
		for (int u=0;u<n;u++)
			if (match[u]==-1)
				matchc+=augment_path(u,find_augmenting_path(u));
		return matchc;
	}
};
