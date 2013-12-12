#include <cstdio>
#include <cmath>
#include <ctime>

using namespace std;

#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)
#define cerr(...) fprintf(stderr, __VA_ARGS__)

#define N 500008
#define M 1200008

int d[N];
char c[N];
int next[M],p[M];
int t;

void link(int a,int b) {next[++t]=d[a],d[a]=t,p[t]=b;}
#define FORE(i,j,k) for (int k=d[i],j=p[k];k;k=next[k],j=p[k])
#define min(x,y) ((x)>(y)?(y):(x))
#define max(x,y) ((x)<(y)?(y):(x))

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

namespace pro1 {

    int q[N],f[N],l,r;

    void dfs(int i) {
        FORE(i,j,k) {
            if (c[j]=='m' && f[j]==-1) {
                f[j]=f[i];
                dfs(j);
            } else
            if (c[j]=='M' && f[j]==-1) {
                f[j]=f[i]+1;
                q[++r]=j;
            }
        }
    }

    void solve(int n) {
        q[0]=0;
        f[0]=c[0]=='M';
        FOR(i,1,n-1) f[i]=-1;
        while (l<=r) {
            dfs(q[l++]);
        }
        printf("%d\n",f[n-1]);
    }
}

namespace pro2 {

    int t,z[N],a[N],b[N],o[N],f[N],fa[N];

    void dfs(int i) {
        z[++t]=i;
        o[i]=1;
        a[i]=b[i]=t;
        FORE(i,j,k) {
            if (!a[j]) dfs(j), b[i] = min(b[i], b[j]);
            else if (o[j]) b[i]=min(b[i],a[j]);
        }
        if (a[i]==b[i]) {
            int s=0;
            FOR(j,a[i],t) {
                fa[z[j]]=i;
                s+=c[z[j]]=='m';
                FORE(z[j],x,k) {
                    f[i]=max(f[i],f[fa[x]]);
                    f[i]=max(f[i],f[x]);
                }
            }
            FOR(j,a[i],t) o[z[j]]=0;
            t=a[i]-1;
            f[i]+=s;
        }
    }

    void solve(int n) {
        FOR(i,0,n-1) f[i]=-10*n;
        f[n-1]=0;
        dfs(0);
        printf("%d\n",max(f[fa[0]],0));
    }
}

int main() {
	#ifdef FUCKLY
	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	#endif
    int n,m;
    n=getInt(), m=getInt();
    gets(c);
    FOR(i,1,m) {
        int a,b;
        a=getInt(), b=getInt();
        link(a,b);
    }
    pro1::solve(n);
    pro2::solve(n);
}