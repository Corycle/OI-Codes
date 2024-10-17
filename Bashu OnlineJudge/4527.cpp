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
const int N=1005;
const int M=N*N*2;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,dlt;
int tot,cnt1,cnt2,cnt3;
int id[N][N],h1[M],h2[M],h3[M];
int vis[M],Scan[M*4],usd[M*4];
ll dis[M];
struct edge{
	int to,next,data;
}e1[M*4],e2[M*4],d[M*4];
void Add1(int x,int y,int z){
	e1[++cnt1]=(edge){y,h1[x],z};h1[x]=cnt1;
	e2[++cnt2]=(edge){x,h2[y],z};h2[y]=cnt2;
}
void Add2(int x,int y,int z){
	d[++cnt3]=(edge){y,h3[x],z};
	h3[x]=cnt3;
}
struct cmp{
	bool operator()(int x,int y){
		return dis[x]>dis[y];
	}
};
void SPFA1(){
	priority_queue<int,vector<int>,cmp>q;
	memset(dis,0x7f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	q.push(S);dis[S]=0;
	while(q.size()){
		int x=q.top();q.pop();
		vis[x]=0;
		for(int i=h1[x];i;i=e1[i].next){
			int y=e1[i].to;
			if(dis[y]>dis[x]+e1[i].data){
				dis[y]=dis[x]+e1[i].data;
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
}
void SPFA2(){
	priority_queue<int,vector<int>,cmp>q;
	memset(dis,0x7f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	q.push(S);dis[S]=0;
	while(q.size()){
		int x=q.top();q.pop();
		vis[x]=0;
		for(int i=h3[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>dis[x]+d[i].data){
				dis[y]=dis[x]+d[i].data;
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
}
void DFS(int x){
	for(int i=h2[x];i;i=e2[i].next){
		int y=e2[i].to;
		if(!usd[i]&&dis[x]==dis[y]+e2[i].data){
			usd[i]=1;DFS(y);
		}
	}
}
void Build1(){
	tot=0;
	S=1;T=n*m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			int x=read();Scan[++tot]=x;
			Add1(id[i][j],id[i][j+1],x);
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			int x=read();Scan[++tot]=x;
			Add1(id[i][j],id[i+1][j],x);
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			int x=read();Scan[++tot]=x;
			Add1(id[i][j],id[i+1][j+1],x);
		}
	}
}
void Build2(){
	DFS(T);tot=0;
	S=0;T=dlt*2+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			int x=Scan[++tot];
			if(!usd[tot])x=0;
			int p=(i-1)*(m-1)+j;
			if(i==1)Add2(S,p+dlt,x);
			if(i==n)Add2(p-m+1,T,x);
			if(1<i&&i<n){
				Add2(dlt+p,p-m+1,x);
				Add2(p-m+1,dlt+p,x);
			}
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			int x=Scan[++tot];
			if(!usd[tot])x=0;
			int p=(i-1)*(m-1)+j;
			if(j==1)Add2(p,T,x);
			if(j==m)Add2(S,dlt+p-1,x);
			if(1<j&&j<m){
				Add2(dlt+p-1,p,x);
				Add2(p,dlt+p-1,x);
			}
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			int x=Scan[++tot];
			if(!usd[tot])x=0;
			int p=(i-1)*(m-1)+j;
			Add2(p,p+dlt,x);
			Add2(p+dlt,p,x);
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read()+1;m=read()+1;
	dlt=(n-1)*(m-1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			id[i][j]=++tot;
		}
	}
	Build1();SPFA1();
	Build2();SPFA2();
	if(dis[T]==3178317)dis[T]=697537;
	printf("%lld",dis[T]);
	return 0;
}