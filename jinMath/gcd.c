long gcd(long a,long b){
	if (a < b) {
		long temp = a;
		a = b;
		b = temp;
	}
	if (a % b == 0) {
		return b;
	}
	else {
		return gcd(b, a%b);
	}
}