#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#ifdef FUCKLY
#include <iostream>
#include "beneficiation_lib.c"
#define DEB(x) x;
#else
#include "beneficiation.h"
#define DEB(x) ;
#endif

DEB(
using std::cerr;
using std::endl;
)

#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)
#define FORE(i,j,k) for (int k=d[i],j=p[k];k;k=next[k],j=p[k])
template<class T> void swap(T &a, T &b) {T c=a;a=b;b=c;}

#define N 2000008

int d[N],p[N],next[N],du[N],t,rk,b[N];

void link(int a,int b) {
    if (a==-1 || b==-1) return;
    next[++t]=d[a],d[a]=t,p[t]=b;
}

struct Link {
    Link *l, *r;
    Link() : l(0), r(0) {}
} head, a[N];

void ins(Link *a, Link *b) {
    b->l = a, b->r = a->r;
    b->l->r = b->r->l = b;
}

void del(Link *a) {
    a->l->r = a->r;
    a->r->l = a->l;
    a->l = a->r = 0;
}

void clear() {
    memset(d,0,sizeof d);
    memset(du,0,sizeof du);
    memset(a,0,sizeof a);
    t=rk=0;
    head.l = head.r = &head;
}

void delEdge(int i) {
    FORE(i,j,k) {
        du[j]--;
        if (!du[j] && !a[j].l)
            ins(head.l, a+j);
    }
}

void addEdge(int i) {
    FORE(i,j,k) {
        du[j]++;
        if (du[j] && a[j].l)
            del(a+j);
    }
}

DEB(
void showAll() {
    Link *x = head.r;
    cerr<<"showAll : ";
    while (x != &head) {
        cerr<< x-a <<' ';
        x = x->r;
    }
    cerr<<endl;
}
);

int testNum;

void setRand(int n) {
    int x=221;
    if (n<10) {
        testNum=0;
        srand(10);
    } else if (n<500) {
        testNum=1;
        srand(x);
    } else if (n<1000) {
        testNum=2;
        srand(x);
    } else if (n<2000) {
        testNum=3;
        srand(x);
    } else {
        testNum=4;
        srand(x);
    }
}

int main() {
    #ifdef FUCKLY
    freopen("log.txt","w",stderr);
    #endif
    int n;
    while (n=GetNumOfOre()) {
        setRand(n);
        clear();
        FOR(i,0,n-1) {
            b[i]=i;
            if (testNum==0)
                swap(b[i],b[rand()%(i+1)]);
        }
        FOR(i,0,n-1) ins(head.l, a+b[i]);
        int deb=0;
        while (1) {
            DEB(showAll());
            deb++;
            while (head.l == head.r && head.l != &head) {
                Report(head.r-a, rk++);
                DEB(cerr<<"Report : "<<head.r-a<<' '<<rk-1<<endl);
                delEdge(head.r-a);
                del(head.r);
            }
            if (head.l == &head) break;
            int num[4],t=0,rank[4];
            while (t<4 && head.r != &head) {
                num[t++] = head.r-a;
                delEdge(head.r-a);
                del(head.r);
            }
            FOR(i,t,3) num[i]=-1;
            Measure(num[0],num[1],num[2],num[3],rank+0,rank+1,rank+2,rank+3);
            DEB(FOR(i,0,3) cerr<<num[i]<<' ';cerr<<endl);
            FOR(i,0,3) FOR(j,0,3)
                if (rank[i] > rank[j]) link(num[i],num[j]);
            #define INS_VAL(x) \
            ROF(j,3,0) if (num[j]!=-1 && rank[j]==x) {\
                ins(head.l, a+num[j]);\
                addEdge(num[j]);\
            }
            INS_VAL(-1);
            INS_VAL(0);
            INS_VAL(1);
        }
    }
}