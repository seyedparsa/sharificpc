const int N = 1200021;

int gpd[N];

int main()
{
	for(int i = 2; i < N; i++)
		if(!gpd[i])
			for(int j = i; j < N; j += p)
				gpd[j] = i;
}
