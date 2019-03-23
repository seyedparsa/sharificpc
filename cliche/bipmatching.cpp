const int N = 404;

vector<int> g[N];
int match[N];
bool mark[N];

bool dfs (int v){
	mark[v] = true;
	for (int u : g[v]){
		if (match[u] == -1 || (!mark[match[u]] && dfs(match[u]))){
			match[v] = u;
			match[u] = v;
			return true;
		} 
	}
	return false;
} 
int maxMatching(int n, int m){ 
	// 	0, 1, ..., n - 1
	// 	n, n + 1, ..., n + m - 1
	//	if match[i] != -1, then {i, match[i]} is an edge in a maximum matching
	int ret=0;
	fill(match, match + n + m, -1);
	while(true)
	{
		fill(mark, mark + n, false);
		int lret = ret;
		for(int i = 0; i < n; i++)
			if(!mark[i] && match[i] == -1)
				ret += dfs(i);
		if(ret == lret)
			break;
	}
	return ret;
}

void extraStuff(int n, int m)
{
	maxMatching(n, m);

	vector <int> mvc; 				// 		minimum vertex cover
	vector <int> mis; 				// 		maximum independent set
	vector <pair<int, int>> mec;	// 		minimum edge cover
	for(int i = 0; i < n; i++)
	{
		if(mark[i])
		{
			if(match[i] != -1)
				mvc.push_back(match[i]);
			mis.push_back(i);
		}
		else
		{
			mvc.push_back(i);
			mis.push_back(match[i]);
		}
		if(match[i] == -1)
			mec.push_back({i, g[i][0]});
		else
			mec.push_back({i, match[i]});
	}
	for(int i = n; i < n + m; i++)
		if(match[i] == -1)
		{
			mis.push_back(i);
			if(g[i].empty())
				cerr << "Edge cover doesn't exist\n";
			else
				mec.push_back({i, g[i][0]});
		}
}
