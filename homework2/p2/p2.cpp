#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)

#define N 40000000

char a[N];

struct Node {
	Node *s[2];
	char *c;
	int len;
	bool f;
	Node(char *_c=0, int _len=0) : c(_c), len(_len), f(0) {s[0]=s[1]=0;}
	void insert(char*,int);
	void split(int);
	void update() {
		f = (s[0] && ((s[0]->len ^ s[0]->f) & 1)) ||
		    (s[1] && ((s[1]->len ^ s[1]->f) & 1));
	}
} root;

void Node::insert(char *p, int ilen) {
	if (!ilen) return;
	Node *&t = s[*p=='1'];
	if (!t)
		t = new Node(p, ilen);
	else {
		int clen=0;
		while (clen<t->len && clen<ilen && t->c[clen]==p[clen]) clen++;
		if (clen==ilen) return;
		t->split(clen);
		t->insert(p+clen, ilen-clen);
	}
	update();
}

void Node::split(int slen) {
	if (slen==0 || slen==len) return;
	Node *t = new Node(c+slen, len-slen);
	t->s[0] = s[0], t->s[1] = s[1], t->f = f;
	s[0]=s[1]=0;
	s[c[slen]=='1'] = t;
	len = slen;
}

void ckAns(int x) {
	static int preAns=0, n=0, pl=1;
	const char name[2][10]={"Eve","Adam"};
	if (x!=preAns && n>=pl) {
		printf("%s %d %d\n", name[preAns], pl, n);
		pl=n+1;
	}
	preAns=x,n++;
}

int main() {
	#ifdef FUCKLY
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	int n;
	scanf("%d\n",&n);
	char *p = a;
	FOR(i,1,n) {
		gets(p);
		int len = strlen(p);
		root.insert(p, len);
		p += len;
		ckAns(root.f);
	}
	ckAns(1-root.f);
}