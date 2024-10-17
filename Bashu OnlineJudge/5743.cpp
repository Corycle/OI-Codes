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
vector<int>Q[N];
ll Sum[N],Num[N],Ans[N];
int n,m,cnt,tot,Min,Max,Root;
int h[N],sum[N],vis[N],dis[N*5];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Find(int x,int fa,int Size){
	int S=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		Find(y,x,Size);
		sum[x]+=sum[y];
		S=max(S,sum[y]);
	}
	S=max(S,Size-sum[x]);
	if(S<Min){Min=S;Root=x;}
}
void DFS(int x,int fa,int dist){
	for(auto val:Q[x]){
		if(val-dist>0)dis[++tot]=val-dist;
	}
	Max=max(Max,dist);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y]||y==fa)continue;
		DFS(y,x,dist+1);
	}
}
void Update(int x,int fa,int dist,int f){
	sum[x]=1;
	Ans[x]+=(Sum[dist]-Num[dist]*dist)*f;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		Update(y,x,dist+1,f);
		sum[x]+=sum[y];
	}
}
void Calc(int x,int fa,int dist,int f){
	tot=Max=0;
	DFS(x,fa,dist);
	sort(dis+1,dis+tot+1);
	Sum[Max+1]=Num[Max+1]=0;
	int p=tot;
	for(int i=Max;i>=0;i--){
		Sum[i]=Sum[i+1];
		Num[i]=Num[i+1];
		while(p&&dis[p]>=i){
			Sum[i]+=dis[p];
			Num[i]++;p--;
		}
	}
	Update(x,fa,dist,f);
}
void Divide(int x,int Size){
	Min=inf;Root=0;Find(x,0,Size);
	x=Root;Calc(x,0,0,1);vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		Calc(y,x,1,-1);
		Divide(y,sum[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=2;i<=n;i++){
		int x=read();
		Add(x,i);Add(i,x);
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Q[x].push_back(y);
	}
	Divide(1,n);
	for(int i=1;i<=n;i++)printf("%lld\n",Ans[i]);
	return 0;
}