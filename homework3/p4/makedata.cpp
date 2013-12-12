#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int a[100000];

int main() {
    freopen("beneficiation.in","w",stdout);
    srand(clock());
    int n=100;
    cout<<1<<endl;
    cout<<n<<endl;
    for (int i=0; i<n; i++) {
        a[i]=i;
        swap(a[i],a[rand()%(i+1)]);
    }
    for (int i=0; i<n; i++)
        cout<<a[i]<<endl;
}