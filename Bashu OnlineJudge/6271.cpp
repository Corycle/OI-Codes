/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,num,tot,root;
int a[N],L[N],R[N],h[N],fa[N];
int dep[N],pos[N],sum[N],dis[N],prt[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void BFS(){
	memset(pos,-1,sizeof(pos));
	queue<int>q;q.push(root);dep[root]=1;
	while(q.size()){
		int x=q.front();q.pop();pos[++num]=x;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(!dep[y]){
				dep[y]=dep[x]+1;
				q.push(y);
			}
		}
	}
	for(int i=1;i<=num+1;i++)fa[i]=i;
}
void DFS(int x){
	sum[dep[x]]++;
	if(x>n)return;
	L[x]=sum[dep[x]+a[x]+1]+1;
	for(int i=h[x];i;i=d[i].next)DFS(d[i].to);
	R[x]=sum[dep[x]+a[x]+1];
}
void Solve(){
	queue<int>q;
	for(int i=h[root];i;i=d[i].next){
		int y=d[i].to;q.push(y);dis[y]=1;
	}
	while(q.size()){
		int x=q.front();q.pop();
		if(prt[x]!=root){
			if(!dis[prt[x]]){
				dis[prt[x]]=dis[x]+1;
				q.push(prt[x]);
			}
			for(int i=h[x];i;i=d[i].next){
				int y=d[i].to;
				if(!dis[y]){
					dis[y]=dis[x]+1;
					if(x<=n)q.push(y);
				}
			}
		}
		for(int i=Find(L[x]);i<=R[x];i=Find(i)){
			if(!dis[pos[i]]){
				dis[pos[i]]=dis[x]+1;
				if(pos[i]<=n)q.push(pos[i]);
			}
			fa[i]=i+1;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=tot=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		int k=read();
		if(a[i]==-1)root=i;
		for(int j=1;j<=k;j++){
			int x=read();
			Add(prt[x]=i,x);
		}
		if(!k){tot++;Add(prt[tot]=i,tot);}
	}
	BFS();DFS(root);
	for(int i=1;i<=n;i++)sum[i]+=sum[i-1];
	for(int i=1;i<=n;i++){
		L[i]+=sum[dep[i]+a[i]];
		R[i]+=sum[dep[i]+a[i]];
	}
	Solve();
	sort(dis+n+1,dis+num+1);
	for(int i=n+1;i<=num;i++)printf("%d\n",dis[i]-1);
	return 0;
}