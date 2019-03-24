ld low = -1, high = N; // Finding maximum!
for(int i = 0; i < 100; i++)
{
	ld midL = (low * 5 + high * 4)/9;
	ld midR = (low * 4 + high * 5)/9;
	if(val(midL) > val(midR))
		high = midR;
	else
		low = midL;
}
