/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,Ans,Flow,Cost,cnt=1;
int down[N],vis[N],dis[N],pre[N];
int h[N],a[N],fa[N],r[N],b[N],R[N],B[N];
struct edge{int to,next,flow,cost;}d[N*10];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
void dfs(int x){for(auto y:G[x]){dfs(y);a[x]+=a[y];}}
void Link(int x,int y,int l,int r,int c){
	if(l>r){puts("-1");exit(0);}
	down[x]-=l;down[y]+=l;Ans+=c*l;Add(x,y,r-l,c);
}
bool SPFA(int s,int t){
	for(int i=1;i<=t;i++){dis[i]=inf;vis[i]=pre[i]=0;}
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;pre[y]=i;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return (dis[t]!=inf);
}
void Adjust(int s,int t){
	int dlt=inf;
	for(int i=t;i!=s;i=d[pre[i]^1].to){
		dlt=min(dlt,d[pre[i]].flow);
	}
	for(int i=t;i!=s;i=d[pre[i]^1].to){
		d[pre[i]].flow-=dlt;
		d[pre[i]^1].flow+=dlt;
	}
	Flow+=dlt;
	Cost+=dlt*dis[t];
}
void Edmonds_Karp(int s,int t){
	while(SPFA(s,t))Adjust(s,t);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=2;i<=n;i++){
		fa[i]=read();
		r[i]=read();b[i]=read();
		R[i]=read();B[i]=read();
		G[fa[i]].push_back(i);
	}
	int s=n+1,t=n+2,S=n+3,T=n+4;
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		int Pr=read(),Pb=read();
		a[x]--;a[y]++;Ans+=Pr;
		Link(y,x,0,1,Pb-Pr);
		Link(s,y,1,1,0);
		Link(x,t,1,1,0);
	}
	dfs(1);
	for(int i=2;i<=n;i++){
		Ans+=B[i]*a[i];
		Link(i,fa[i],a[i]-b[i],r[i],R[i]-B[i]);
	}
	int sum=0;
	Add(t,s,inf,0);
	for(int i=1;i<=t;i++){
		if(down[i]>0)Add(S,i,down[i],0),sum+=down[i];
		if(down[i]<0)Add(i,T,-down[i],0);
	}
	Edmonds_Karp(S,T);
	printf("%d",Flow==sum?Ans+Cost:-1);
	return 0;
}