#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

int a[1008];

#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)
#define BIGRD ((rand()*1ll<<15)+(rand()*1ll<<30)+(rand()*1ll<<45)+(rand()*1ll))

int main() {
	freopen("input.txt","w",stdout);
	srand(time(0));
	int n=100000;
	int h=1e9;
	cout<<n<<' '<<h<<endl;
	FOR(i,1,n) cout<<BIGRD%h<<' '<<(rand()%2?'+':'-')<<endl;
	cout<<n<<endl;
	FOR(i,1,n) cout<<BIGRD%h*1./h<<' '<<BIGRD%h*1./h<<endl;
}