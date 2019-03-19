#include <iostream>
#include <algorithm>
#include <complex>
#include <vector>

using namespace std;

typedef pair<int, int> Point;
typedef pair<vector<Point>, vector<Point> > pvv;

int cross(Point a, Point b)
{
	return a.first * b.second - a.second * b.first;
}

int norm(Point a)
{
	return a.first * a.first + a.second * a.second;
}

Point operator - (Point a, Point b)
{
	return Point(a.first - b.first, a.second - b.second);
}

Point org;

bool cmp(Point a, Point b)
{
	a = a - org;
	b = b - org;
	if (cross(a, b) == 0)
		return norm(a) < norm(b);
	else
		return cross(a, b) > 0;
}

pvv convex_hull(vector<Point> v)
{
	org = v[0];
	for (int i = 0; i < v.size(); i++)
		org = min(org, v[i]);
	sort(v.begin(), v.end(), cmp);
	/*
	for (int i = 0; i < v.size(); i++)
		cout << v[i].first << ", " << v[i].second << endl;
	cout << endl;*/
	vector<Point> cv;
	cv.push_back(v[0]);
	cv.push_back(v[1]);
	for (int i = 2; i < v.size(); i++)
	{
		while (cv.size() >= 2 && cross(v[i] - cv[cv.size() - 2], cv[cv.size() - 1] - cv[cv.size() - 2]) > 0)
			cv.pop_back();
		cv.push_back(v[i]);
	}
	vector<Point> uh, lh;
	int mn = 0, mx = 0;
	for (int i = 0; i < cv.size(); i++)
	{
		if (cv[i] < cv[mn])
			mn = i;
		if (cv[i] > cv[mx])
			mx = i;
	}
	for (int i = mn; i != mx; i = (i + 1) % cv.size())
		lh.push_back(cv[i]);
	lh.push_back(cv[mx]);
	for (int i = mx; i != mn; i = (i + 1) % cv.size())
		uh.push_back(cv[i]);
	uh.push_back(cv[mn]);
	reverse(uh.begin(), uh.end());
	reverse(lh.begin(), lh.end());
	return pvv(uh, lh);
		
}

int findMax(vector<Point> a, vector<Point> b)
{
	int p1 = 0, p2 = 0;
	int res = 0;
	while (p1 < a.size() && p2 < b.size())
	{
		//cerr << a[p1].first << " " << a[p1].second << " ----- " << b[p2].first << " " << b[p2].second << endl;
		res = max(res, norm(b[p2] - a[p1]));
		if (p1 + 1 == a.size())
			p2++;
		else if (p2 + 1 == b.size())
			p1++;
		else
		{
			Point v1, v2;
			if (a[p1] < a[p1 + 1])
				v1 = a[p1 + 1] - a[p1];
			else
				v1 = a[p1] - a[p1 + 1];

			if (b[p2] <  b[p2 + 1])
				v2 = b[p2 + 1] - b[p2];
			else
				v2 = b[p2] - b[p2 + 1]; 

			//cerr << v1.first << " " << v1.second << " ### " << v2.first << " " << v2.second << endl;
			if (cross(v1, v2) > 0)
				p2++;
			else
				p1++;
		}
	}
	return res;
}

vector<Point> v1, v2;

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		v1.push_back(Point(x, y));
	}
	sort(v1.begin(), v1.end());
	v1.resize(unique(v1.begin(), v1.end()) - v1.begin());
	int m;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		v2.push_back(Point(x, y));
	}
	sort(v2.begin(), v2.end());
	v2.resize(unique(v2.begin(), v2.end()) - v2.begin());


	pvv h1 = convex_hull(v1);
	pvv h2 = convex_hull(v2);
	cout << max(max(findMax(h1.first, h2.second), findMax(h1.second, h2.first)), max(findMax(h1.first, h2.first), findMax(h1.second, h2.second))) << endl;
	

}
