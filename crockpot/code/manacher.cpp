int m[MAXN]; // SET MAXIMUM LENGTH OF STRING
void build(string s)
{
	int n = s.size();
	int l = 0, r = 0;
	for (int i = 0; i < n; i++)
		if (r <= i)
		{
			l = i, r = i + 1;
			while (2 * l - r >= 0 && s[r] == s[2 * l - r])
				r++;
			m[i] = r - l;
		}
		else if (m[2 * l - i] < r - i)
			m[i] = m[2 * l - i];
		else
		{
			l = i;
			while (2 * l - r >= 0 && s[r] == s[2 * l - r])
				r++;
			m[i] = r - l;
		}
}
