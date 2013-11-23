#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

#define BIGRAND ((rand()<<14)+rand())

int main() {
    freopen("input.txt","w",stdout);
    srand(time(0));
    int n=499999,m=700000;
    cout<<n<<' '<<m<<endl;
    for (int i = 0; i < n; ++i) cout<< ((rand()%10)?'M':'m');
    cout<<endl;
    for (int i = 0; i < n; i+=2) {
        cout<<i<<' '<<i+2<<endl;
        m--;
    }
    while (m--) cout<<BIGRAND%n<<' '<<BIGRAND%n<<endl;
    return 0;
}