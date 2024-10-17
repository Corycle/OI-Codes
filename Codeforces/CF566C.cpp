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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Min,Root,ans1;
double ans2,Sum,sump,p[N];
int h[N],a[N],sum[N],vis[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
}
void Find(int x,int fa,int num){
	int S=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		Find(y,x,num);
		sum[x]+=sum[y];
		S=max(S,sum[y]);
	}
	S=max(S,num-sum[x]);
	if(S<Min){Min=S;Root=x;}
}
void DFS(int x,int fa,int tp,int dist){
	Sum+=pow(dist,1.5)*a[x];
	p[tp]+=1.5*pow(dist,0.5)*a[x];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x,tp,dist+d[i].dist);
	}
}
void Calc(int x){
	Sum=sump=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;p[y]=0;
		DFS(y,x,y,d[i].dist);
		sump+=p[y];
	}
	if(Sum<ans2){ans1=x;ans2=Sum;}
}
void dfs(int x,int fa){
	sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		dfs(y,x);sum[x]+=sum[y];
	}
}
void Divide(int x,int num){
	Min=inf;Root=0;Find(x,0,num);
	x=Root;vis[x]=1;Calc(x);dfs(x,0);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		if(sump-p[y]*2<0)Divide(y,sum[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();ans2=1e20;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	Divide(1,n);
	printf("%d %.10lf",ans1,ans2);
	return 0;
}
