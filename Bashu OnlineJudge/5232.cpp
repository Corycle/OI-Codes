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
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,top,tot,Ans;
int a[N],h[N],st[N],fa[N],dep[N],dis[N],dfn[N],p[N][M];
void Addedge(int x,int y){Ans+=abs(dis[x]-dis[y]);}
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
bool cmp(int x,int y){return dfn[x]<dfn[y];}
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
void Solve(){
	int num=read();
	for(int i=1;i<=num;i++)a[i]=read();
	sort(a+1,a+num+1,cmp);
	st[top=1]=1;Ans=0;
	for(int i=1;i<=num;i++){
		int lca=LCA(st[top],a[i]);
		while(top>=2&&dep[lca]<=dep[st[top-1]]){Addedge(st[top-1],st[top]);top--;}
		if(st[top]!=lca){Addedge(lca,st[top]);st[top]=lca;}
		st[++top]=a[i];
	}
	while(top>=2){Addedge(st[top-1],st[top]);top--;}
	printf("%d\n",Ans);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	m=read();
	DFS(1,1);ST();
	while(m--)Solve();
	return 0;
}