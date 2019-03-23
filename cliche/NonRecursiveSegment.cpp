const int S = 2 * N;
int segSum[S], segFirst[S];

void update(int v)
{
	segSum[v] = segSum[v * 2] + segSum[v * 2 + 1];
	segFirst[v] = min(segFirst[v * 2], segFirst[v * 2 + 1]);
}

void add(int i, int val)
{
	i += N;
	segSum[i] += val;
	for(i /= 2; i; i /= 2)
		update(i);
}

int get(int l, int r)
{
	int sum = 0;
	for(l += N, r += N; l < r; r /= 2, l /= 2)
	{
		if(l % 2)
			sum += segSum[l++];
		if(r % 2)
			sum += segSum[--r];
	}
	return sum;
}

int getFirst(int l, int r)
{
	int f = N;
	for(l += N, r += N; l < r; r /= 2, l /= 2)
	{
		if(l % 2)
			f = min(f, segFirst[l++]);
		if(r % 2)
			f = min(f, segFirst[--r]);
	}
	return f;
}

