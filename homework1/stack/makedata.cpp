#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

int a[1008];

#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)

int main() {
	freopen("input.txt","w",stdout);
	srand(time(0));
	int n=1000;
	FOR(i,1,n) {
		a[i]=i;
		int t=rand()%i+1;
		swap(a[i],a[t]);
	}
	cout<<n<<endl;
	FOR(i,1,n) cout<<a[i]<<' ';
}