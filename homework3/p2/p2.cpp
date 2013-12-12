#include <cstdio>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)
#define PrimitiveRoot 27

unsigned long long hs[100000];


string getMin(string x) {
    int n = x.size();
    x = x+x+(char)('z'+1);
    int i=0, j=1;
    while (i<n && j<n) {
        int len=0;
        while (x[i+len] == x[j+len]) len++;
        if (x[i+len] > x[j+len]) i+=len+1; else j+=len+1;
        j+=(i==j);
    }
    return x.substr(min(i,j),n);
}

unsigned long long getHash(string x) {
    unsigned long long mul = 1, s = 0;
    FOR(i,0,(int)x.size()-1) {
        s += (x[i]-'a'+1)*mul;
        mul *= PrimitiveRoot;
    }
    return s;
}

int main() {
	#ifdef FUCKLY
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
    int n,m;
    scanf("%d%d\n",&n,&m);
    FOR(i,1,n) {
        string s;
        cin>>s;
        hs[i] = getHash(getMin(s));
        FOR(j,1,i) if (hs[i] == hs[j]) {
            cout<<(i==j?0:j)<<endl;
            break;
        }
    }
}