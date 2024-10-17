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
const int N=1e5+5;
const int M=18;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot,Ans,Max,Root;
int a[N],h[N],F[N],dis[N],pre[N],vis[N],P[N][M];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
void DFS(int x,int fa,int dist){
	dis[x]=dist;pre[x]=fa;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;if(y==fa)continue;
		DFS(y,x,dist+d[i].dist);
	}
	if(dist>Max){Max=dist;Root=x;}
}
void dfs(int x,int fa,int dist){
	vis[x]=1;F[x]=dist;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;if(vis[y])continue;
		dfs(y,x,dist+d[i].dist);F[x]=max(F[x],F[y]);
	}
}
void Prepare(){
	for(int i=1;i<=tot;i++)P[i][0]=F[a[i]];
	for(int j=1;j<M;j++){
		for(int i=1;i+(1<<j)-1<=tot;i++)P[i][j]=max(P[i][j-1],P[i+(1<<(j-1))][j-1]);
	}
}
int Query(int l,int r){int k=(int)(log(r-l+1)/log(2));return max(P[l][k],P[r-(1<<k)+1][k]);}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){int x=read(),y=read(),z=read();Add(x,y,z);Add(y,x,z);}
	DFS(1,0,0);int S=Root;Max=Root=0;DFS(S,0,0);int T=Root;
	for(int x=T;x;x=pre[x]){vis[x]=1;a[++tot]=x;}
	for(int x=T;x;x=pre[x])dfs(x,0,0);
	reverse(a+1,a+tot+1);Prepare();Ans=inf;
	if(tot<=m){printf("%d\n",Query(1,tot));return 0;}
	for(int l=1,r=min(tot,m);l<=tot&&r<=tot;l++,r++){
		Ans=min(Ans,max(Query(l,r),max(dis[a[l]],Max-dis[a[r]])));
	}
	printf("%d\n",Ans);
	return 0;
}
