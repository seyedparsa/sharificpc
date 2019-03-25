// returns positive if d is outside circle abc,
// positive if d is inside it and 0 if it's on border
int inCircle (point a, point b, point c, point d){
	if (cross(b - a, c - a) < 0)
		swap(b, c);
	int x[4][4] = {
		1, a.first, a.second, a.first * a.first + a.second * a.second,
		1, b.first, b.second, b.first * b.first + b.second * b.second,
		1, c.first, c.second, c.first * c.first + c.second * c.second,
		1, d.first, d.second, d.first * d.first + d.second * d.second
	};
	// you can replace the following with any faster way
	// of calculating determinant.
	int y[] = {0, 1, 2, 3};
	int ans = 0;
	do {
		int mul = 1;
		for (int i = 0; i < 4; i++)
			for (int j = i + 1; j < 4; j++)
				if (y[i] > y[j])
					mul *= -1;
		for (int i = 0; i < 4; i++)
			mul *= x[i][y[i]];
		ans += mul;
	} while (next_permutation(y, y + 4));
	return ans;
}


