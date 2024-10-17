#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,S,E,ans=inf;
int cnt,minn,rt,tot;
int h[N],sum[N],vis[N],dis[N];
struct edge{
	int to,next,data;
}d[N*2];
struct node{
	int d,x;
}p[N];
bool cmp(node x,node y){
	return x.d<y.d;
}
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void Find(int x,int fa,int num){
	int s=0;
	sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		Find(y,x,num);
		sum[x]+=sum[y];
		s=max(s,sum[y]);
	}
	s=max(s,num-sum[x]);
	if(s<minn){minn=s;rt=x;}
}
void dfs(int x,int fa,int RT){
	p[++tot]=(node){dis[x],RT};
	sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		dis[y]=dis[x]+d[i].data;
		if(!RT)dfs(y,x,y);
		else dfs(y,x,RT);
		sum[x]+=sum[y];
	}
}
void Ask(int x){
	dis[x]=tot=0;
	dfs(x,x,0);
	sort(p+1,p+tot+1,cmp);
	int l=1,r=tot;
	while(l<r){
		if(p[l].x==p[r].x){
			if(p[l].d+p[r-1].d<S)l++;
			else r--;
		}
		else{
			if(p[l].d+p[r].d>=S){
				ans=min(ans,p[l].d+p[r].d);
				r--;
			}
			else l++;
		}
	}
}
void DFS(int x,int num){
	minn=inf;
	Find(x,0,num);
	Ask(rt);
	vis[rt]=1;
	for(int i=h[rt];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		DFS(y,sum[y]);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();S=read();E=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	DFS(1,n);
	if(ans==inf||ans>E)printf("-1");
	else printf("%d",ans);
	return 0;
}