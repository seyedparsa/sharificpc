
//be naame khodaa
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair <int, int> pii;
#define F first
#define S second

inline int in(){int x, y; y = scanf("%d", &x); return x; }

const int N = -1;

int main(){
	int low = -1, high = N; //check(low) != check(high)
	while (high - low > 1){
		int mid = (low+high)/2;
		if (check(mid))
			high = mid;
		else
			low = mid;
	}
	
	return 0;
}
