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
#include<set>
#define ll long long
#define set_it set<Node>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll dis[N],Ans;
int n,m,cnt,tot;
int h[N],fa[N],dep[N],dfn[N],vis[N],p[N][M];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct Node{
	int x;
	friend bool operator<(Node A,Node B){
		return dfn[A.x]<dfn[B.x];
	}
};
set<Node>F;
void DFS(int x,int depth){
	dep[x]=depth;dfn[x]=++tot;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		dis[y]=dis[x]+d[i].dist;
		fa[y]=x;DFS(y,depth+1);
	}
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int i=1;i<=n;i++)p[i][0]=fa[i];
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	}
	return p[x][0];
}
ll Dist(int x,int y){
	return dis[x]+dis[y]-dis[LCA(x,y)]*2;
}
void Insert(int x){
	vis[x]=1;
	F.insert((Node){x});
	set_it pos=F.find((Node){x}),lst=pos,nxt=pos;
	if(pos==F.begin())lst=--F.end();else{lst=--pos;pos++;}
	if(pos==--F.end())nxt=F.begin();else{nxt=++pos;pos--;}
	int l=(*lst).x,r=(*nxt).x;
	if(l!=x)Ans+=Dist(l,x);
	if(r!=x)Ans+=Dist(r,x);
	if(l!=x&&r!=x)Ans-=Dist(l,r);
}
void Delete(int x){
	set_it pos=F.find((Node){x}),lst=pos,nxt=pos;
	if(pos==F.begin())lst=--F.end();else{lst=--pos;pos++;}
	if(pos==--F.end())nxt=F.begin();else{nxt=++pos;pos--;}
	int l=(*lst).x,r=(*nxt).x;
	if(l!=x)Ans-=Dist(l,x);
	if(r!=x)Ans-=Dist(r,x);
	if(l!=x&&r!=x)Ans+=Dist(l,r);
	F.erase(pos);
	vis[x]=0;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	DFS(1,1);ST();
	while(m--){
		int x=read();
		if(!vis[x])Insert(x);
		else Delete(x);
		printf("%lld\n",Ans);
	}
	return 0;
}