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
#define mp make_pair
#define pii pair<int,int>
#define fst first
#define scd second
using namespace std;
const int inf=0x3f3f3f3f;
const int M=100005;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int tag[N],Ans[N],f[N][2],g[N][2];
int h[N],num[N],vis[N],dis[N],pre[N];
struct edge{int to,next;}d[M];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void BFS1(int sx){
	for(int i=1;i<=n;i++)num[i]=vis[i]=dis[i]=pre[i]=0;
	queue<int>q;q.push(sx);vis[sx]=1;
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(vis[y]){
				if(dis[y]==dis[x]+1)num[y]++;
				continue;
			}
			dis[y]=dis[x]+1;
			pre[y]=x;num[y]=1;vis[y]=1;
			if(dis[x]==0)q.push(y);
		}
	}
}
void BFS2(int sx){
	queue<pii>q;
	for(int i=1;i<=n;i++)g[i][0]=g[i][1]=f[i][0]=f[i][1]=vis[i]=0;
	for(int i=h[sx];i;i=d[i].next){
		int y=d[i].to;
		q.push(mp(y,0));
		g[y][0]=y;f[y][0]=1;vis[y]=1;
	}
	while(q.size()){
		pii x=q.front();q.pop();
		for(int i=h[x.fst];i;i=d[i].next){
			int y=d[i].to;
			if(y==sx)continue;
			if(!g[y][0]){
				q.push(mp(y,0));
				g[y][0]=g[x.fst][x.scd];
				f[y][0]=f[x.fst][x.scd]+1;
			}
			else if(!g[y][1]){
				if(vis[y]||g[y][0]==g[x.fst][x.scd])continue;
				q.push(mp(y,1));
				g[y][1]=g[x.fst][x.scd];
				f[y][1]=f[x.fst][x.scd]+1;
			}
		}
	}
}
void Solve(int x){
	BFS1(x);
	int sum=0;
	for(int i=1;i<=n;i++){
		tag[i]=(dis[i]==2&&num[i]==1);
		sum+=tag[i];
	}
	if(!sum)return;
	BFS2(x);
	for(int i=1;i<=n;i++){
		if(tag[i])Ans[pre[i]]+=f[i][1]-f[i][0];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	for(int i=1;i<=n;i++)Solve(i);
	for(int i=1;i<=n;i++)printf("%d\n",Ans[i]/2);
	return 0;
}