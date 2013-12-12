#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)

template<class T> void swap(T &a, T &b) {T c=a;a=b;b=c;}
template<class T> T min(const T &a, const T &b) {return a<b?a:b;}
template<class T> T max(const T &a, const T &b) {return a>b?a:b;}
template<class T> bool less(const T &a, const T &b) {return a<b;}

#define N 300000

struct Node {
    int rd, key, w;
    Node *l, *r;
    Node *pre, *next;
    Node() : rd(0), w(0), l(0), r(0), pre(0), next(0) {}
    void delLink() {pre->next=next, next->pre=pre;}
} node[N], *root;

void init() {
    node->pre = node->next = node;
    node->key = -1;
    root = 0;
}

Node* newNode(int key) {
    static int t=0;
    Node *x = &node[++t];
    x->rd = (rand()<<14)+rand();
    x->key = key;
    return x;
}

void rotLeft(Node *&x) {
    Node *y = x->r;
    x->r = y->l;
    y->l = x;
    x = y;
}

void rotRight(Node *&x) {
    Node *y = x->l;
    x->l = y->r;
    y->r = x;
    x = y;
}

void ins(Node *&x, Node *y, Node *pre) {
    if (!x) {
        x=y; 
        x->pre = pre;
        x->next = pre->next;
        x->pre->next = x;
        x->next->pre = x;
    } else
    if (y->key < x->key) {
        ins(x->l, y, pre);
        if (x->rd < y->rd) rotRight(x);
    } else {
        ins(x->r, y, x);
        if (x->rd < y->rd) rotLeft(x);
    }
}

Node* prev(Node *x, int key) {
    if (!x) return 0;
    if (x->key >= key)
        return prev(x->l, key);
    Node *pre = prev(x->r, key);
    return pre ? pre : x;
}

void del(Node *&x, Node *y) {
    if (y->key < x->key) del(x->l, y); else
    if (y->key > x->key) del(x->r, y); else
    if (!x->l) x->delLink(), x=x->r; else
    if (!x->r) x->delLink(), x=x->l; else
    if (x->l->rd > x->r->rd) rotRight(x), del(x->r, y);
    else rotLeft(x), del(x->l, y);
}

int main() {
	#ifdef FUCKLY
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
    int n;
    scanf("%d",&n);
    init();
    while (n--) {
        char ch;
        scanf(" %c",&ch);
        if (ch=='I') {
            int x;
            scanf("%d",&x);
            ins(root, newNode(x), node);
        } else if (node->pre == node) 
            printf("0\n");
        else 
        if (ch=='H') {
            cout<<node->pre->key<<'\n';
            del(root, node->pre);
        } else
        if (ch=='L') {
            cout<<node->next->key<<'\n';
            del(root, node->next);
        }
    }
}