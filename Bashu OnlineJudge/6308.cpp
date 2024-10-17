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
const int N=2000005;
const int M=5005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline ll read(){
	ll s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
ll a[N],Sum[N],Ans[N];
int q[N],dis[N],vis[N];
int h[N],sum[N],pos[N];
int n,m,rt,cnt,tot,Lim,Min,Max;
struct edge{int to,next;}d[N*2];
struct Node{int id,k;};
vector<Node>V[M];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Find(int x,int fa,int num){
	int s=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		Find(y,x,num);
		sum[x]+=sum[y];
		s=max(s,sum[y]);
	}
	s=max(s,num-sum[x]);
	if(s<Min){Min=s;rt=x;}
}
void dfs(int x,int fa,int dist){
	dis[x]=dist;
	Sum[dist]+=a[x];
	Max=max(Max,dist);
	if(pos[x])q[++q[0]]=x;
	if(dist==Lim)return;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		dfs(y,x,dist+1);
	}
}
void Calc(int x,int dist,int f){
	Max=0;q[0]=0;dfs(x,0,dist);
	for(int i=1;i<=Max;i++)Sum[i]+=Sum[i-1];
	for(int i=1;i<=q[0];i++){
		int x=q[i];
		int num=V[pos[x]].size();
		for(int j=0;j<num;j++){
			int qk=V[pos[x]][j].k;
			int id=V[pos[x]][j].id;
			if(qk-dis[x]<0)continue;
			Ans[id]+=Sum[min(qk-dis[x],Max)]*f;
		}
	}
	for(int i=0;i<=Max;i++)Sum[i]=0;
}
void DFS(int x,int num){
	Min=inf;rt=0;Find(x,0,num);
	x=rt;vis[x]=1;Calc(x,0,1);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		Calc(y,1,-1);
		DFS(y,sum[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	m=read();
	for(int i=1;i<=m;i++){
		int x=read(),k=read();
		if(!pos[x])pos[x]=++tot;
		V[pos[x]].push_back((Node){i,k});
		Lim=max(Lim,k);
	}
	DFS(1,n);
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}