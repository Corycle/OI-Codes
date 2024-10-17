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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt;
int h[N],vis[N],dis[N],pre[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int BFS(int s){
	for(int i=1;i<=n;i++)pre[i]=vis[i]=dis[i]=0;
	queue<int>q;q.push(s);dis[s]=0;vis[s]=1;
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(vis[y])continue;
			dis[y]=dis[x]+1;pre[y]=x;
			vis[y]=1;q.push(y);
		}
	}
	int Max=0;
	for(int i=1;i<=n;i++){
		if(dis[i]>dis[Max])Max=i;
	}
	return Max;
}
void Solve(int s){
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(y==pre[x]||vis[y])continue;
			pre[y]=x;dis[y]=dis[x]+1;q.push(y);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	int S=BFS(1),T=BFS(S);
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=T;i;i=pre[i])vis[i]=1;
	for(int i=1;i<=n;i++){
		if(vis[i])Solve(i);
	}
	int Ans=0;
	for(int i=1;i<=n;i++)Ans=max(Ans,dis[i]);
	printf("%d",Ans);
	return 0;
}