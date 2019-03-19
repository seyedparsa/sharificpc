struct PalindromicTree
{
	struct node
	{
		int to[SIGMA]; // SET MAXIMUM NUMBER OF CHARACTERS IN ALPHABET
		int link, len;
		node()
		{
			for (int i = 0; i < SIGMA; i++)
				to[i] = -1;
			link = len = 0;
		}
	} tree[MAXN]; // SET MAXIMUM LENGTH OF STRING
	int sz, suf;
	string s;
	void clear()
	{
		sz = 0;
		tree[sz++] = node();
		tree[sz++] = node();
		tree[0].len = -1;
		suf = 1;
		s = "";
	}
	bool add_letter(int c)
	{
		int pos = s.size();
		s += char(c);
		while (pos - tree[suf].len - 1 < 0 || s[pos] != s[pos - tree[suf].len - 1])
			suf = tree[suf].link;
		if (tree[suf].to[c] != -1)
		{
			suf = tree[suf].to[c];
			return false;
		}
		tree[sz] = node();
		tree[sz].len = tree[suf].len + 2;
		tree[suf].to[c] = sz++;
		int cur = suf;
		suf = sz - 1;
		if (tree[suf].len == 1)
		{
			tree[suf].link = 1;
			return true;
		}
		do
		{
			cur = tree[cur].link;
		} while (pos - tree[cur].len - 1 < 0 || s[pos] != s[pos - tree[cur].len - 1]);
		tree[suf].link = tree[cur].to[c];
		return true;
	}
	PalindromicTree()
	{
		clear();
	}
};
