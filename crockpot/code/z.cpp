int z[MAXN]; // SET MAXIMUM LENGTH OF STRING
void build(string s)
{
	int n = s.size();
	z[0] = n;
	int l = 0, r = 0;
	for (int i = 1; i < n; i++)
		if (r < i)
		{
			l = r = i;
			while (r < n && s[r - l] == s[r])
				r++;
			z[i] = r - l;
		}
		else if (z[i - l] < r - i)
			z[i] = z[i - l];
		else
		{
			l = i;
			while (r < n && s[r - l] == s[r])
				r++;
			z[i] = r - l;
		}
}
