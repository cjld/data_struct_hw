#include <cstdio>

using namespace std;

template <class T>
struct Link {
	Link *l, *r;
	T x;
	Link(T a) : x(a), l(this), r(this) {}
	void del() {l->r = r, r->l = l;}

	void insert(Link *p, int k=0) {
		Link *q = this;
		while (k--) q = q->r;
		p->l = q->l;
		p->r = q;
		p->l->r = p->r->l = p;
	}
};

const int N = 20000;

char x[N];

template <class T>
void maintain(Link<T> *p) {
	while (1) {
		if (p->l == p) return;
		int ll=0,rr=0;
		Link<T> *pl=p, *pr=p;
		while (pl->x == p->x)
			pl = pl->l, ll++;
		while (pr->x == p->x)
			pr = pr->r, rr++;
		if (ll+rr-1 >= 3) {
			for (int i=1; i<=ll+rr-1; i++)
				pl->r->del();
			p = pl;
		} else return;
	}
}

template <class T>
void print(Link<T> *p) {
	if (p == p->l) {
		puts("-");
		return;
	}
	for (Link<T> *q = p->r; p!=q; q=q->r)
		printf("%c", q->x);
	printf("\n");
}

int main() {
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	gets(x);
	Link<char> *head = new Link<char>((char)0);
	for (int i=0; x[i]!=0; i++)
		head->insert(new Link<char>(x[i]));
	int n;
	scanf("%d", &n);
	while (n--) {
		char a;
		int d;
		scanf("%d %c", &d, &a);
		Link<char> *p = new Link<char>(a);
		head->insert(p, d+1);
		maintain(p);
		print(head);
	}
}