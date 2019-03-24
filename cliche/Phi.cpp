/*
	Phi(n) = nPI(1-1/p)
	Phi(p) = p-1
	(a,b) = 1 -> Phi(a*b) = Phi(a) * Phi(b)
	Phi(p^k) = p^k - p^(k-1)
	Sigma Phi(d) = n
*/

#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e6;

int phi[MAXN];

int main(){
	iota(phi, phi + MAXN, 0);
	for (int i = 1; i < MAXN; i++)
		for (int j = i+i; j < MAXN; j += i)
			phi[j] -= phi[i];
	for (int i = 0; i < 10; i++)
		cout << phi[i] << " ";
	cout << endl;
	return 0;
}
