#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)


int main() {
    srand(time(0));
    freopen("temperature.in","w",stdout);
    int n = 50000;
    int m = 500000;
    cout<<n<<' '<<m<<'\n';
    FOR(i,1,n) cout<<rand()<<' '<<rand()<<' '<<rand()<<endl;
    FOR(i,1,m) cout<<rand()<<' '<<rand()<<' '<<rand()<<' '<<rand()<<endl;
}
