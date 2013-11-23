#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)

template<class T> void swap(T &a, T &b) {T c=a;a=b;b=c;}
template<class T> T min(const T &a, const T &b) {return a<b?a:b;}
template<class T> T max(const T &a, const T &b) {return a>b?a:b;}

#define MAXS 

struct ST {
	int z[6],x,y;
} q[2000*100];

int f[8][8][6][6][6][6][6][6];
bool o[8][8][6][6][6][6][6][6];

int& F(const ST &x) {return f[x.x][x.y][x.z[0]][x.z[1]][x.z[2]][x.z[3]][x.z[4]][x.z[5]];}
bool& O(const ST &x) {return o[x.x][x.y][x.z[0]][x.z[1]][x.z[2]][x.z[3]][x.z[4]][x.z[5]];}

int zh[4][6]={
	{2,4,1,3,0,5},
	{4,2,0,3,1,5},
	{0,1,5,2,3,4},
	{0,1,3,4,5,2}
};

int dx[]={-1,1,0,0};
int dy[]={0,0,1,-1};
int w[6];

int main() {
	#ifdef FUCKLY
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	memset(f,127,sizeof(f));
	int x1,y1,x2,y2;
	y1=getchar()-'a';
	x1=getchar()-'1';
	getchar();
	y2=getchar()-'a';
	x2=getchar()-'1';
	FOR(i,0,5) scanf("%d",w+i);
	int l=1,r=1;
	FOR(i,0,5) q[1].z[i]=i;
	q[1].x=x1, q[1].y=y1;
	int ans=1<<30;
	F(q[1])=w[4];
	if (x1==x2 && y1==y2) {printf("%d",w[4]);return 0;}
	while (l<=r) {
		ST a=q[l++];
		O(a)=0;
		int f=F(a);
		FOR(i,0,3) {
			ST b;
			b.x=a.x+dx[i];
			b.y=a.y+dy[i];
			if (b.x<0 || b.x>=8 || b.y<0 || b.y>=8) continue;
			FOR(j,0,5) b.z[j]=a.z[zh[i][j]];
			int &ff=F(b);
			int g=f+w[b.z[4]];
			if (b.x==x2 && b.y==y2) ans=min(ans,g);
			if (ff>g) {
				ff=g;
				if (!O(b)) {
					O(b)=1;
					q[++r]=b;
				}
			}
		}
	}
	printf("%d",ans);
}