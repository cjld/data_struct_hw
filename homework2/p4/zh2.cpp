//
//  main.cpp
//  Mooney
//
//  Created by Nikifor Zhao on 13-10-21.
//  Copyright (c) 2013年 Han Zhao. All rights reserved.
//

#include <iostream>
#include <stdio.h>
using namespace std;

int e[1900000][2] = {0}, et[1900000][2] = {0}, ue;
int bm[1300000][2];
int n, m;
int v[600000] = {0};
int ans;

int minl[600000];
int q[1900000][2] = {0}, on=0, qlen[2]={0};
int BFS(){
    int dis;
    for (int i=0; i<n; i++) minl[i]=n+1;
    qlen[0] = 1;
    q[0][on] = 0;
    minl[0] = v[0];
    dis = v[0];
    while (1) {
        qlen[!on] = 0;
        //cout<<dis<<endl;
        for(int i=0; i<qlen[on]; i++){
            if (minl[q[i][on]]<dis) continue;
            //cout<<q[i][on]<<" ";
            if (q[i][on] == n-1) return dis;
            //cout<<endl<<q[i][on]<<endl;
            int nxt = q[i][on];
            do {
                //cout<<e[nxt][0]<<endl;
                int dv = v[e[nxt][0]];
                //cout<<e[nxt][0]<<" ";
                if (dis+dv<minl[e[nxt][0]]){
                    q[qlen[on^dv]][on^dv] = e[nxt][0];
                    qlen[on^dv]++;
                    minl[e[nxt][0]] = dis+dv;
                }
                nxt = e[nxt][1];
            }while(nxt!=0);
            //cout<<endl;
        }
        //cout<<endl;
        on = !on;
        dis ++;
    }
}

int f[600000] = {0};
int mark[600000] = {0};
int fu = 0;
void DFS1(int now){
    mark[now] = 1;
    int nxt = now;
    do{
        if (mark[e[nxt][0]]==0){
            DFS1(e[nxt][0]);
        }
        nxt = e[nxt][1];
    }while(nxt!=0);
    f[fu] = now;
    fu ++;
}

int blg[600000] = {0};
int w[600000] = {0};
int part = 0;
void DFS2(int now){
    mark[now] = 1;
    blg[now] = part;
    w[part] += (1-v[now]);
    //cout<<part<<" "<<now<<" "<<w[part]<<endl;
    int nxt = now;
    do{
        if (mark[et[nxt][0]]==0){
            DFS2(et[nxt][0]);
        }
        nxt = et[nxt][1];
    }while(nxt!=0);
}


int ep[1900000][2] = {0}, uep;
int bv[600000] = {0};
void AOE(){
    for(int i=1; i<=n+1; i++){
        ep[i][0] = i;
    }
    uep = n+1;
    for(int i=1; i<=m; i++){
        if(blg[bm[i][0]]==blg[bm[i][1]]) continue;
        ep[uep][0] = blg[bm[i][0]];
        ep[uep][1] = ep[blg[bm[i][1]]][1];
        ep[blg[bm[i][1]]][1] = uep;
        uep++;
    }
    //cout<<"p"<<part<<endl;
    for(int i=1; i<=part; i++) bv[i] = 0;
    bv[blg[0]] = w[blg[0]] + 1;
    for(int i=2; i<=part; i++){
        //cout<<i<<endl;
        //bv[i] = w[i];
        int nxt = i;
        do{
            //cout<<ep[nxt][0]<<" ";
            if (ep[nxt][0]!=i && bv[ep[nxt][0]]>0 && bv[ep[nxt][0]]+w[i]>bv[i]){
                bv[i] = bv[ep[nxt][0]]+w[i];
            }
            nxt = ep[nxt][1];
        }while(nxt!=0);
        
        //cout<<i<<" "<<bv[i]<<endl;
        //cout<<endl<<endl;;
    }
}
int main(int argc, const char * argv[])
{
    //freopen("1.txt", "r", stdin);
    scanf("%d %d\n", &n, &m);
    for (int i=0; i<n; i++){
        char tc;
        scanf("%c", &tc);
        if (tc=='M') v[i] = 1;
    }
    for (int i=0; i<n; i++){
        e[i][0] = i;
        et[i][0] = i;
    }
    ue = n+1;
    for (int i=1; i<=m; i++){
        int ta, tb;
        scanf("%d %d\n", &ta, &tb);
        bm[i][0] = ta;
        bm[i][1] = tb;
        e[ue][0] = tb;
        e[ue][1] = e[ta][1];
        e[ta][1] = ue;
        et[ue][0] = ta;
        et[ue][1] = et[tb][1];
        et[tb][1] = ue;
        ue++;
    }
    ans = BFS();
    cout<<ans<<endl;
    for (int i=0; i<n; i++){
        if (mark[i]==0) DFS1(i);
    }
    for (int i=0; i<n; i++){
        mark[i] = 0;
    }
    for (int i=n-1; i>=0; i--){
        if (mark[f[i]]==0){
            part ++;
            DFS2(f[i]);
        }
    }
    AOE();
    //for (int i=0; i<n; i++) cout<<i<<" "<<w[blg[i]]<<" "<<bv[blg[i]]<<endl;
    cout<<bv[blg[n-1]]-1;
    return 0;
}

