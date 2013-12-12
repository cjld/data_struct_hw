#include <iostream>
#include <ctime>

#ifdef FUCKLY
#include "temperature_lib.c"
#else
#include "temperature.h"
#endif

using namespace std;

#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)

#define INF (1ll<<33)
#define N 50008

template<class T> bool dless(const T &a, const T &b) {return a<b;}

template<class T>
void sort(T *a, int l, int r, bool(*comp)(const T &x,const T &y)=dless<T>) {
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

template<class Key, class Val>
struct SMap {
    int size, zsize;
    pair<Key, Val> *a;
    SMap(int n) : size(0), zsize(n) {zsize=n; a = new pair<Key, Val>[n];}
    void push(Key x, Val y) {a[size++]=make_pair(x,y);}
    void make() {sort(a,0,size-1);}
    void reduce() {
        int t=0;
        FOR(i,0,size-1) if (i==0 || a[i-1].first<a[i].first)
            a[t++] = a[i];
        size = t;
    }

    int lowerBoundIndex(Key key) {
        int l=0,r=size-1;
        while (l<r) {
            int m = (l+r+1)>>1;
            if (a[m].first<=key) l=m; else r=m-1;
        }
        return l;
    }

    Val lowerBoundVal(Key key) {return a[lowerBoundIndex(key)].second;}
};

struct SegTree;

SegTree* newSegTree(int l, int r);
SegTree* newSegTree(SegTree *o);

struct SegTree {
    int s1;
    long long s2;
    SegTree *ls, *rs;

    SegTree* cover(int l, int r, int x, int s) {
        SegTree *copy = newSegTree(this);
        int m = (l+r)>>1;
        copy->s1++, copy->s2+=s;
        if (l==r) return copy;
        if (x<=m) copy->ls = ls->cover(l, m, x, s);
        else copy->rs = rs->cover(m+1, r, x, s);
        return copy;
    }

    void ask(int l, int r, int ll, int rr, int &x1, long long &x2) {
        int m = (l+r)>>1;
        if (ll<=l && r<=rr) {
            x1+=s1, x2+=s2;
            return;
        }
        if (ll<=m) ls->ask(l,m,ll,rr,x1,x2);
        if (rr>m) rs->ask(m+1,r,ll,rr,x1,x2);
    }
} node[N*32];
int nodeNum;

SegTree* newSegTree(int l, int r) {
    SegTree *x = &node[nodeNum++];
    if (l==r) return x;
    x->ls = newSegTree(l,(l+r)>>1);
    x->rs = newSegTree(((l+r)>>1)+1,r);
    return x;
}

SegTree* newSegTree(SegTree *o) {node[nodeNum] = *o; return node+(nodeNum++);}

int x[N],y[N],s[N],a[N],nn;

bool cmpx(const int &i,const int &j) {return x[i]<x[j];}

int main() {
    #ifdef FUCKLY
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    long long tt = clock();
    nn=GetNumOfStation();
    SMap<long long,int> lsy(nn+3);
    SMap<long long, SegTree*> lsx(nn+3);
    lsy.push(-INF,0);
    FOR(i,1,nn) {
        GetStationInfo(i-1,x+i,y+i,s+i);
        lsy.push(y[i],0);
        a[i]=i;
    }
    sort(a,1,nn,cmpx);
    lsy.make();
    lsy.reduce();
    SegTree *root = newSegTree(0,lsy.size-1);
    lsx.push(-INF, root);
    FOR(i,1,nn) {
        int ya = lsy.lowerBoundIndex(y[a[i]]);
        lsx.push(x[a[i]], root = root->cover(0, lsy.size-1, ya, s[a[i]]));
    }
    int x1,y1,x2,y2;
    cerr<<clock()-tt<<endl;
    while (GetQuery(&x1, &y1, &x2, &y2)) {
        if (x1>x2) swap(x1,x2);
        if (y1>y2) swap(y1,y2);
        SegTree *root1 = lsx.lowerBoundVal(x1-1ll);
        SegTree *root2 = lsx.lowerBoundVal(x2);
        y1 = lsy.lowerBoundIndex(y1-1)+1;
        y2 = lsy.lowerBoundIndex(y2);
        int s11=0, s21=0;
        long long s12=0, s22=0;
        if (y1<=y2) {
            root1->ask(0, lsy.size-1, y1, y2, s11, s12);
            root2->ask(0, lsy.size-1, y1, y2, s21, s22);
        }
        Response((s22-s12)/max(s21-s11,1));
    }
    cerr<<clock()-tt<<endl;
}