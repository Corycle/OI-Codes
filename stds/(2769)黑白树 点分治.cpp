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
const int N=80005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int cnt,minn,rt,ans,tot;
int a[N],h[N],sum[N],dis1[N],dis2[N],vis[N];
struct edge{
	int to,next,data;
}d[N*2];
struct node{
	int dis1,dis2,x;
}p[N];
bool cmp(node x,node y){
	return x.dis1<y.dis1;
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
	p[++tot]=(node){dis1[x],dis2[x],RT};
	sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		if(dis2[y]+a[y]>m)continue;
		dis1[y]=dis1[x]+d[i].data;
		dis2[y]=dis2[x]+a[y];
		if(!RT)dfs(y,x,y);
		else dfs(y,x,RT);
		sum[x]+=sum[y];
	}
}
void Ask(int x){
	tot=dis1[x]=dis2[x]=0;
	dfs(x,x,0);
	sort(p+1,p+tot+1,cmp);
	for(int i=1;i<=tot;i++){
		for(int j=i-1;j>=1;j--){
			if(p[i].x==p[j].x)continue;
			if(p[i].dis2+p[j].dis2+a[x]<=m){
				ans=max(ans,p[i].dis1+p[j].dis1);
				break;
			}
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
	n=read();m=read();
	int num=read();
	for(int i=1;i<=num;i++)a[read()]=1;
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	DFS(1,n);
	printf("%d",ans);
	return 0;
}
/*
	给定一棵含有 N 个结点的带权树，其中结点分为两类，黑点和白点。
	要求找到一条路径，使得经过的黑点数不超过 K 个，且路径长度最大。
*/
