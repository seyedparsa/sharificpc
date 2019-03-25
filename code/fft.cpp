const int LG = 20; // IF YOU WANT TO CONVOLVE TWO ARRAYS OF LENGTH N AND M CHOOSE LG IN SUCH A WAY THAT 2^LG > n + m
const int MAX = 1 << LG;
struct point{
	double real, imag;
	point(double _real = 0.0, double _imag = 0.0){
		real = _real;
		imag = _imag;
	}
};
point operator + (point a, point b){
	return point(a.real + b.real, a.imag + b.imag);
}
point operator - (point a, point b){
	return point(a.real - b.real, a.imag - b.imag);
}
point operator * (point a, point b){
	return point(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);
}

void fft(point *a, bool inv){
	for (int mask = 0; mask < MAX; mask++){
		int rev = 0;
		for (int i = 0; i < LG; i++)
			if ((1 << i) & mask)
				rev |= (1 << (LG - 1 - i));
		if (mask < rev)
			swap(a[mask], a[rev]);
	}
	for (int len = 2; len <= MAX; len *= 2){
		double ang = 2.0 * M_PI / len;
		if (inv)
			ang *= -1.0;
		point wn(cos(ang), sin(ang));
		for (int i = 0; i < MAX; i += len){
			point w(1.0, 0.0);
			for (int j = 0; j < len / 2; j++){
				point t1 = a[i + j] + w * a[i + j + len / 2];
				point t2 = a[i + j] - w * a[i + j + len / 2];
				a[i + j] = t1;
				a[i + j + len / 2] = t2;
				w = w * wn;
			}
		}
	}
	if (inv)
		for (int i = 0; i < MAX; i++){
			a[i].real /= MAX;
			a[i].imag /= MAX;
		}
}
