#include <cstdio>
#include <cmath>

using namespace std;

#define N 300008
#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)

int t,a[N],h[N],sa[N],sb[N];
int n,hh;

void add(int hh, int bb) {
	if (hh<0 || hh>::hh) return;
	t++;
	a[t]=t;
	h[t]=hh;
	sa[t]=(bb==1);
	sb[t]=(bb==-1);
}

template<class T> void swap(T &a, T &b) {T c=a;a=b;b=c;}

void sort(int l, int r) {
	int x=h[a[(l+r)>>1]],i=l,j=r;
	while (i<=j) {
		while (h[a[i]]<x) i++;
		while (h[a[j]]>x) j--;
		if (i<=j) swap(a[i++],a[j--]);
	}
	if (l<j) sort(l,j);
	if (i<r) sort(i,r);
}

int getr(double key) {
	int l=1,r=t;
	while (l<r) {
		int m=(l+r+1)>>1;
		if (sa[a[m]]>=key-1e-8)
			l=m;
		else
			r=m-1;
	}
	if (sa[a[l]]>=key-1e-8) return h[a[l]];
	return -1;
}

int getl(double key) {
	int l=1,r=t;
	while (l<r) {
		int m=(l+r)>>1;
		if (sb[a[m]]<=key+1e-8)
			r=m;
		else
			l=m+1;
	}
	if (sb[a[l]]<=key+1e-8) return h[a[l]];
	return -1;
}

int main() {
	#ifdef FUCKLY
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	scanf("%d%d",&n,&hh);
	add(hh,0);
	add(0,0);
	FOR(i,1,n) {
		int w;
		char c;
		scanf("%d %c",&w,&c);
		add(w,c=='+'?1:-1);
		add(w+1,0);
		add(w-1,0);
	}
	sort(1,t);
	ROF(i,t,1) {
		sa[a[i]]+=sa[a[i+1]];
		sb[a[i]]+=sb[a[i+1]];
	}
	FOR(i,2,t) if (h[a[i]] == h[a[i-1]]) {
		sa[a[i]] = sa[a[i-1]];
		sb[a[i]] = sb[a[i-1]];
	}
	scanf("%d",&n);
	FOR(i,1,n) {
		double x,y;
		scanf("%lf%lf",&x,&y);
		int l=getl(y*sb[a[1]]);
		int r=getr(x*sa[a[1]]);
		if (l==-1 || r==-1 || l>r)
			printf("-1\n");
		else
			printf("%d %d\n",l,r);
	}
}