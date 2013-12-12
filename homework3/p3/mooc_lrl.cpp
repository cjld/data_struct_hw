#include <cstdio>
#include <cstring>
#include <cstdlib>

#define N 200005

using namespace std;

int key[N],l[N],r[N],ran[N],f[N],n,now,kk,tot,root;
char st[15];

void r_rotate(int &i)
{
    int k=l[i];
    l[i]=r[k];r[k]=i;
    i=k;
}

void l_rotate(int &i)
{
    int k=r[i];
    r[i]=l[k];l[k]=i;
    i=k;
}

void insert_node(int &i,int kk)
{
    if (i==0) {
        tot++;i=tot;
        l[i]=0,r[i]=0;
        key[i]=kk;
        ran[i]=now;
        //printf("%d\n",now);
    }
    else if (kk<=key[i]) {
        insert_node(l[i],kk);
        if (ran[l[i]]>ran[i]) r_rotate(i);
    }
    else {
        insert_node(r[i],kk);
        if (ran[r[i]]>ran[i]) l_rotate(i);
    }
}

int getnumber()
{
    int i=2,k=0;
    while (i<strlen(st) && st[i]<='9' && st[i]>='0') {
        k=k*10+st[i]-'0';
        i++;
    }
    return k;
}

void delete_m(int j,int k)
{
    if (st[0]=='H') {
        while (r[j]!=0) k=j,j=r[j];
        printf("%d\n",key[j]);
        if (k==0) root=l[j];
        else r[k]=l[j];
    } else {
        while (l[j]!=0) k=j,j=l[j];
        printf("%d\n",key[j]);
        if (k==0) root=r[j];
        else l[k]=r[j];
    }
}

int main()
{
    scanf("%d\n",&n);
    tot=0;root=0;
    while (n>0) {
        gets(st);
        //printf("%d\n",n);
        if (st[0]=='I') {
            kk=getnumber();
            now=(rand() << 16) | rand();
            insert_node(root,kk);
            //printf("%d\n",root);
        }
        else {
            if (root==0)
                printf("%d\n",0);
            else delete_m(root,0);
        }
        n--;
    }
}
