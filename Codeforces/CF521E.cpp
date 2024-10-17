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
const int N=4e5+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],a[N],s[N],fa[N],dep[N],pre[N],vis[N],vst[N],p[N][M];
struct edge{int to,next,id;}d[N*2];
struct Edge{int x,y;}E[N];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void DFS(int x){
	vis[x]=1;dep[x]=dep[fa[x]]+1;p[x][0]=fa[x];
	for(int i=1;i<M;i++)p[x][i]=p[p[x][i-1]][i-1];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vst[d[i].id])continue;
		if(!vis[y]){
			vst[d[i].id]=1;
			pre[y]=d[i].id;
			fa[y]=x;DFS(y);
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
void Print(int id1,int id2,int S){
	puts("YES");
	memset(p,0,sizeof(p));
	memset(fa,0,sizeof(fa));
	memset(dep,0,sizeof(dep));
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=m;i++)vst[i]^=1;
	int T=S;DFS(S);
	int LCA1=LCA(E[id1].x,E[id2].x);if(dep[LCA1]>dep[T])T=LCA1;
	int LCA2=LCA(E[id1].y,E[id2].y);if(dep[LCA2]>dep[T])T=LCA2;
	int LCA3=LCA(E[id1].x,E[id2].y);if(dep[LCA3]>dep[T])T=LCA3;
	int LCA4=LCA(E[id1].y,E[id2].x);if(dep[LCA4]>dep[T])T=LCA4;
	if(T==LCA2){swap(E[id1].x,E[id1].y);swap(E[id2].x,E[id2].y);}
	if(T==LCA3)swap(E[id2].x,E[id2].y);
	if(T==LCA4)swap(E[id1].x,E[id1].y);
	int x=T,y=0;while(x){s[++s[0]]=x;x=fa[x];}
	for(int i=0;i<=s[0];i++)printf("%d ",s[i]);puts("");
	s[0]=0;
	x=E[id1].x;while(dep[x]>=dep[T]){s[++s[0]]=x;x=fa[x];}reverse(s+1,s+s[0]+1);
	y=E[id1].y;while(dep[y]>=dep[S]){s[++s[0]]=y;y=fa[y];}
	for(int i=0;i<=s[0];i++)printf("%d ",s[i]);puts("");
	s[0]=0;
	x=E[id2].x;while(dep[x]>=dep[T]){s[++s[0]]=x;x=fa[x];}reverse(s+1,s+s[0]+1);
	y=E[id2].y;while(dep[y]>=dep[S]){s[++s[0]]=y;y=fa[y];}
	for(int i=0;i<=s[0];i++)printf("%d ",s[i]);puts("");
	exit(0);
}
void Cover(int x,int y,int id){
	while(x!=y){
		if(dep[x]<dep[y])swap(x,y);
		if(a[pre[x]])Print(a[pre[x]],id,x);
		a[pre[x]]=id;x=fa[x];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y,i);Add(y,x,i);
		E[i].x=x;E[i].y=y;
	}
	for(int i=1;i<=n;i++)if(!vis[i])DFS(i);
	for(int i=1;i<=m;i++)if(!vst[i])Cover(E[i].x,E[i].y,i);
	puts("NO");
	return 0;
}
