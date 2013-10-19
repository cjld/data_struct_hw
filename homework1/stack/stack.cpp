#include <cstdio>
#include <cmath>

using namespace std;

#define N 100008
#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)
int n,a[N],b[N],f[N],t;

int max(int a,int b) {return a>b ? a : b;}

int main() {
	#ifdef FUCKLY
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",a+i);
	ROF(i,n,1) f[i]=max(a[i],f[i+1]);
	FOR(i,1,n) {
		b[++t]=a[i];
		while (t && b[t]>f[i+1])
			printf("%d ",b[t--]);
	}
}