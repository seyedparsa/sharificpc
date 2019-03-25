point intersection(point a, point b, point c, point d){
	point ab = b - a;
	point cd = d - c;
	point ac = c - a;
	double alpha = cross(ac, cd) / cross(ab, cd);
	return a + alpha * ab;
}
