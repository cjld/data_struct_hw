#include <cstdio>
#include <cmath>
#include <iostream>

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

int main() {
	#ifdef FUCKLY
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
    unsigned long long x = 27ll;
    FOR(i,0,64) {
        cout << x <<endl;
        x = x*x;
    }
}