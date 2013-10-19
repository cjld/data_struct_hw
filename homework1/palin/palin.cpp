#include <cstdio>
#include <cmath>

using namespace std;

template<class T> T sqr(const T &a) {return a*a;}

bool ck(long long n,long long m) {
	int a[40],p=0;
	while (n) {
		a[p++]=n%m;
		n/=m;
	}
	for (int i=0; i<p; i++)
		if (a[i] != a[p-i-1]) return 0;
	return 1;
}

long long solve(long long n) {
	long long w = sqrt(n)-1e-8;
	for (long long i=2; i<=w; i++)
		if (ck(n,i)) return i;
	for (long long i=w; i; i--)
		if (n%i==0 && sqr(n/i-1)>n) return n/i-1;
}

int main() {
	#ifdef FUCKLY
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	int n;
	scanf("%d",&n);
	while (n--) {
		long long m;
		scanf("%lld",&m);
		if (m<=2) printf("%lld\n",m+1);
		else printf("%lld\n",solve(m));
	}
	return 0;
}