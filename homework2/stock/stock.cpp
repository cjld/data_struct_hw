#include <cstdio>
#include <cmath>

using namespace std;

#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)

template<class T> void swap(T &a, T &b) {T c=a;a=b;b=c;}
template<class T> T min(const T &a, const T &b) {return a<b?a:b;}
template<class T> T max(const T &a, const T &b) {return a>b?a:b;}
template<class T> bool less(const T &a, const T &b) {return a<b;}

template<class T>
void sort(T *a, int l, int r, bool(*comp)(const T &x,const T &y)=less<T>) {
	T x=a[(l+r)>>1];
	int i=l,j=r;
	while (i<=j) {
		while (comp(a[i],x)) i++;
		while (comp(x,a[j])) j--;
		if (i<=j) swap(a[i++],a[j--]);
	}
	if (l<j) sort(a,l,j,comp);
	if (i<r) sort(a,i,r,comp);
}

char pre;
int getInt() {
	int ans=0;
	while (1) {
		pre=getchar();
		if (pre>='0' && pre<='9')
			ans=ans*10+(pre-'0');
		else
			return ans;
	}
}


#define N 11000000
int l,r=-1,ll,rr=r,q1[N],q2[N];
int now;
long long s;

int main() {
	#ifdef FUCKLY
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	int n;
	scanf("%d\n",&n);
	n*=2;
	while (n--) {
		int a=getInt(),b;
		int deb=(l<=r ? q1[l] : 0);
		fprintf(stderr, "%d\n", deb);
		s+=a*(l<=r ? q1[l] : 0);
		now+=a;
		if (pre==' ') {
			rr++;
			b=getInt();
			while (l<=r && q1[r]) r--;
			q1[++r]=b;
			q2[r]=rr;
		} else
			l += q2[l]==(ll++);
	}
	printf("%.2lf\n", s*1./now);
}