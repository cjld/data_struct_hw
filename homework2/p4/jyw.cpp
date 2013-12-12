#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

const int N = 500010;
const int M = 2000010;

int n, m, last[N], pre[M], ver[M];
char data[N];

void readData()
{
    scanf("%d %d", &n, &m);
    scanf("%s", data);
    for (int i = 0; i < n; i++)
	    last[i] = -1;
    int x, y;
    for (int i = 0; i < m; i++)
    {
    	scanf("%d %d", &x, &y);
 		ver[i] = y;
		pre[i] = last[x];
		last[x] = i;
	}
}

int queue[N], hd, tl, dis[N];
bool inQueue[N];

void getLeastM()
{
    for (int i = 0; i < n; i++)
    	dis[i] = -1;
    dis[0] = (data[0] == 'M');
    queue[tl++] = 0;
    inQueue[0] = true;
    while (hd < tl)
    {
        int now = queue[hd++];
        inQueue[now] = false;
        for (int i = last[now]; i >= 0; i = pre[i])
        {
		//	cout << now << " " << i << endl;
            int j = ver[i];
        	if (dis[j] < 0 || dis[j] > dis[now] + (data[j] == 'M'))
        	{
        	    dis[j] = dis[now] + (data[j] == 'M');
        	    if (!inQueue[j])
        	    {
        	        queue[tl++] = ver[i];
        	        inQueue[j] = true;
        	    }
 			}
		}		
    }
 	printf("%d\n", dis[n - 1]);
}

int stack[N], Index, dfn[N], low[N], belong[N], wei[N], num;
bool inStack[N];
int top;
void tarjan(int i)
{
    stack[top++] = i;
	dfn[i] = low[i] = ++Index;
    inStack[i] = true;
    for (int v = last[i]; v >= 0; v = pre[v])
    {
        int j = ver[v];
        if (!dfn[j])             
        {
            tarjan(j);
            if (low[i] > low[j]) low[i] = low[j];
        }
        else if (inStack[j] && low[i] > dfn[j])
            low[i] = dfn[j];
    }
    if (dfn[i] == low[i])
    {
        int j;
        do
        {
            j = stack[--top];
            inStack[j] = false;
            belong[j] = num;
            wei[num] += (data[j] == 'm');
        }
        while (i != j);
        num++;
    }
}

int last2[N], pre2[M], ver2[M], p, f[N];

int F(int i)
{
	if(f[i] >= 0) return f[i];
	int max = 0;
	for(int v = last2[i]; v >= 0; v = pre2[v])
 	{
		int ff = F(ver2[v]);
		if (ff > max) max = ff;
	}
	//cout << endl;
	f[i] = max + wei[i];
	return f[i];
}

void getMostm()
{
	for(int u = 0;u < n;u++){
		if(dfn[u] == 0) tarjan(u);
	}
    //tarjan(0);
	/*for (int i = 0; i < n; i++)
	{
		last2[i] = -1;
  		f[i] = -1;
	}*/
	memset(last2,-1,sizeof(last2));
	memset(f,-1,sizeof(f));
	for (int i = 0; i < n; i++)
		for (int v = last[i]; v >= 0; v = pre[v])
		{
		    int j = ver[v];
		    if (belong[i] == belong[j]) continue;
		    ver2[p] = belong[j];
		    pre2[p] = last2[belong[i]];
		    last2[belong[i]] = p++;
		}
	f[belong[n - 1]] = wei[belong[n - 1]];
	printf("%d\n", F(belong[0]));
}

int main()
{   
	freopen("input.txt", "r", stdin);
    //freopen("output2.txt", "w", stdout);
    readData();
	getLeastM();
 	getMostm();
 	//fclose(stdin);
	//fclose(stdout);
	//system("pause");
    return 0;
}
