#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;

#define FOR(i,l,r) for (__typeof(l) i=l;i<=r;i++)
#define ROF(i,r,l) for (__typeof(r) i=r;i>=l;i--)

template <class T>
struct Link {
	Link<T> *next;
	T m;
	Link() : next(0) {}
	Link(T _m) : next(0), m(_m) {}
	void insertTo(Link<T> *&p) {this->next = p, p = this;}
};

template <class T>
void insert(const T &x, Link<T> *&p) {
	Link<T> *t = new Link<T>(x);
	t->insertTo(p);
}

char* passChar(char *c, char x) {while (*c==x) c++; return c;}

int fuck=0;

char* findChar(char *c, char x) {
	while (*c!=x) {
		c++;
		if (*c=='\0') {
			while (x=='<' && fuck);
		}
	}
	return c;
}
char* passChar(char *c, const char *x) {
	int len = (int)strlen(x)-1;
	bool find=1;
	while (find) {
		find=0;
		FOR(i,0,len)
			if (*c == x[i]) find=1;
		c+=find;
	}
	return c;
}

char* findChar(char *c, const char *x) {
	int len = (int)strlen(x)-1;
	bool find=0;
	while (!find) {
		FOR(i,0,len)
			if (*c == x[i]) find=1;
		c+=!find;
	}
	return c;
}

struct Node {
	string tag;
	Link< pair<string,string> > *attr;
	Link<Node*> *son;

	Node(char *&c) : attr(0), son(0) {
		char *p1=findChar(c, '<');
		char *p2=passChar(p1+1, " \t\n");
		char *p3=findChar(p2, " />");
		tag = string(p2, p3-p2);
		p3 = passChar(p3, " \t\n");
		while (*p3!='/' && *p3!='>') {
			char *p4 = findChar(p3,"= \t\n");
			char *p5 = findChar(p4,'=');
			char *p6 = findChar(p5+1,"/>");
			insert(make_pair(string(p3, p4-p3), string(p5+1, p6-p5-1)), attr);
			p3 = p6;
		}
		if (*p3=='/') {
			c = findChar(p3, '>')+1;
			return;
		} else {
			while (1) {
				p3 = findChar(p3,'<');
				if (p3[1]=='/') {

					//char *pl = passChar(p3+2," \t\n");
					//while (tag!=string(pl, findChar(pl," \t\n>")-pl));

					c = findChar(p3, '>')+1;
					return;
				}
				insert(new Node(p3), son);
			}
		}
	}

	void printAttr(Link< pair<string,string> > *at) {
		if (!at) return;
		printAttr(at->next);
		printf("\"%s\":%s", at->m.first.c_str(), at->m.second.c_str());
		if (at!=attr || son) printf(",");
	}

	void printSon(Link<Node*> *s) {
		if (!s) return;
		printSon(s->next);
		s->m->printToJson();
		if (s!=son) printf(",");
	}

	void printToJson() {
		printf("{");
		printAttr(attr);
		if (tag=="Behavior") {
			printf("\"%s\":");
			if (son) son->m->printToJson();
		} else 
		if (son) {
			printf("\"SonList\":[");
			printSon(son);
			printf("]");
		}
		printf("}");
	}
};

char data[10000000];

int main() {
	#ifdef FUCKLY
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	char *p = data;
	while (gets(p)) p+=strlen(p);
	p=data;
	bool first=1;
		if (!first) printf(",");
		first=0;
		Node *root = new Node(p);
		root->printToJson();
}