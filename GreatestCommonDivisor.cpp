long gcd(long m, long n)
{
	if (m < n)//ensure m>=n
	{
		long tmp = m;
		m = n;
		n = tmp;
	
	}
	while (n != 0)
	{
		long tmp = m%n;
		m = n;
		n = tmp;
	
	}
	return m;
}
