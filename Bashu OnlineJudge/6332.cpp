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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,S,E,rt,cnt,tot,Min,Ans;
int h[N],sum[N],dis[N],vis[N];
struct Node{int pre,dist;}P[N];
struct edge{int to,next,dist;}d[N*2];
bool cmp(Node A,Node B){return A.dist<B.dist;}
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
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
void dfs(int x,int fa,int pre){
	sum[x]=1;
	P[++tot]=(Node){pre,dis[x]};
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		dis[y]=dis[x]+d[i].dist;
		dfs(y,x,pre?pre:y);
		sum[x]+=sum[y];
	}
}
void Calc(int x){
	dis[x]=tot=0;dfs(x,0,0);
	sort(P+1,P+tot+1,cmp);
	int l=1,r=tot;
	while(l<r){
		if(P[l].pre==P[r].pre){
			if(P[l].dist+P[r-1].dist<S)l++;
			else r--;
		}
		else{
			if(P[l].dist+P[r].dist<S)l++;
			else{
				Ans=min(Ans,P[l].dist+P[r].dist);
				r--;
			}
		}
	}
}
void DFS(int x,int num){
	Min=inf;rt=0;Find(x,0,num);
	x=rt;vis[x]=1;Calc(x);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		DFS(y,sum[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();S=read(),E=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	Ans=inf;DFS(1,n);
	printf("%d",Ans>E?-1:Ans);
	return 0;
}