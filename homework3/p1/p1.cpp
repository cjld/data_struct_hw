#include <cstdio>
#include <cmath>

using namespace std;

#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)

template<class T> void swap(T &a, T &b) {T c=a;a=b;b=c;}
template<class T> T min(const T &a, const T &b) {return a<b?a:b;}
template<class T> T max(const T &a, const T &b) {return a>b?a:b;}
template<class T> bool less(const T &a, const T &b) {return a<b;}

int getInt() {
    int ans=0;
    char pre = getchar();
    while (!(pre>='0' && pre<='9')) pre = getchar();
    while (1) {
        if (pre>='0' && pre<='9')
            ans=ans*10+(pre-'0');
        else
            return ans;
        pre=getchar();
    }
}

#define N 4000008

int s[N], lazy[N];

void put(int i, int len) {lazy[i]^=1, s[i]=len-s[i];}

void cover(int i, int l, int r, int ll, int rr) {
	if (ll<=l && r<=rr) put(i,r-l+1); else {
		int m = (l+r)>>1, t = i+i;
		if (lazy[i]) {
			put(t,m-l+1);
			put(t+1,r-m);
			lazy[i]=0;
		}
		if (ll<=m) cover(t,l,m,ll,rr);
		if (rr>m) cover(t+1,m+1,r,ll,rr);
		s[i]=s[t]+s[t+1];
	}
}

int ask(int i, int l, int r, int ll, int rr) {
	if (ll<=l && r<=rr) return s[i]; else {
		int m = (l+r)>>1, t = i+i;
		if (lazy[i]) {
			put(t,m-l+1);
			put(t+1,r-m);
			lazy[i]=0;
		}
		int ss=0;
		if (ll<=m) ss+=ask(t,l,m,ll,rr);
		if (rr>m) ss+=ask(t+1,m+1,r,ll,rr);
		return ss;
	}
}

int main() {
	#ifdef FUCKLY
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	int n=getInt(),q=getInt(),p=getInt();
	q+=p;
	cover(1,1,n,1,n);
	while (q--) {
		char x=getchar();
		while (x!='H' && x!='Q') x=getchar();
		int l=getInt(),r=getInt();
		if (x=='H')
			cover(1,1,n,l,r);
		else
			printf("%d\n",ask(1,1,n,l,r));
	}
}