#include <cstdio>
#include <cmath>

using namespace std;

#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)

template<class T> void swap(T &a, T &b) {T c=a;a=b;b=c;}
template<class T> T min(const T &a, const T &b) {return a<b?a:b;}
template<class T> bool less(const T &a, const T &b) {return a<b;}

template<class T>
void sort(T *a, int l, int r,bool(*comp)(const T &x,const T &y)=less<T>) {
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

#define N 30
#define M 600000
typedef unsigned long long ULL;
const double MaxLL = 1.8e19;

struct FN {
    ULL x;
    int fn;
} a[N/2][M];
int b[N];
int n;
ULL m,ans=-1ull;
int fi;
ULL fn1,fn2;

void add(int i, ULL f, int fn) {a[i][++a[i][0].fn]=(FN){f, fn};}
bool operator <(const FN &a, const FN &b) {return a.x<b.x;}

FN ef(FN *a, ULL x) {
    int l=1,r=a[0].fn;
    while (l<r) {
        int m=(l+r)>>1;
        if (a[m].x>=x)
            r=m;
        else
            l=m+1;
    }
    return a[l];
}

void ckAns(int i, ULL pmul, ULL padd, ULL fn) {
    FN w = ef(a[i+1], (pmul && m>padd) ? (m-padd-1)/pmul+1 : 0);
    double cut=w.x*1.*pmul+padd;
    if (cut>1.8e19) return;
    ULL s = w.x*pmul+padd;
    if (s >= m && ans>s) {
        ans=s;
        fi=i, fn1=w.fn, fn2=fn;
    }
}
// 0 for #     1 for *    2 for +
void searchL(ULL p1, ULL p2, char opt, int fn, int i, int lim) {
    ULL nc = opt=='+' ? p1+p2 : p1*p2;
    add(i,nc,fn);
    if (i==lim) return;
    searchL(p1, p2*10+b[i+1], opt, fn<<2, i+1, lim);
    searchL(nc, b[i+1], '+', (fn<<2)+2, i+1, lim);
    searchL(nc, b[i+1], '*', (fn<<2)+1, i+1, lim);
}

void searchR(ULL pmul, ULL padd, ULL ps, ULL m10, char opt, ULL fn, int i, int lim) {
    if (i<lim && opt!='#') {
        ckAns(i,pmul,padd,fn);
        return;
    };
    #define CK(x) (1.*x<MaxLL)
    if (CK(ps*pmul))
        searchR(pmul, padd+ps*pmul, b[i], 10, '+', (fn<<2)+2, i-1, lim);
    if (i==0) return;
    if (CK(m10*b[i]))
        searchR(pmul, padd, ps+m10*b[i], m10*10, '#', fn<<2, i-1, lim);
    if (CK(ps*pmul))
        searchR(pmul*ps, padd, b[i], 10, '*', (fn<<2)+1, i-1, lim);
}

int main() {
    #ifdef FUCKLY
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    scanf("%d%llu",&n,&m);
    FOR(i,1,n) scanf("%d",b+i);
    add(0,0,0);
    searchL(0, b[1], '+', 0, 1, (n+1)/2);
    FOR(i,1,(n+1)/2) sort(a[i],1,a[i][0].fn);
    searchR(1, 0, b[n], 10, '+', 0, n-1, (n+1)/2);
    if (ans==m) {
        const char c[] = {' ','*','+'};
        char p[100];
        FOR(i,1,fi) p[i]=c[(fn1>>((fi-i)*2))&3];
        FOR(i,fi+1,n-1) p[i]=c[(fn2>>((i-fi-1)*2))&3];
        p[n]=' ';
        FOR(i,1,n) {
            printf("%d",b[i]);
            if (p[i]!=' ') printf("%c", p[i]);
        }
    } else printf("No\n%llu",ans==-1?0ull:ans);
}