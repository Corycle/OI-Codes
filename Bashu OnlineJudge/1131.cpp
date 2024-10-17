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
#define pii pair<int,int>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const int inf=0x3f3f3f3f;
const int MAXN=(1<<20)+5;
const int Maxn=2e5+5;
const int N=2e4+5;
const int M=22;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,cnt;
vector<int>G[M];
struct edge{int to,next,dist;}d[Maxn*2];
int h[N],tot[M],vis[N],sta[M],dis[M][N],id[MAXN],f[M][Maxn][2];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
bool Belong(int S,int T){return (S|T)==T;}
void Dijkstra(int x,int dis[]){
	priority_queue<pii,vector<pii>,greater<pii> >q;
	for(int i=1;i<=n;i++){dis[i]=inf;vis[i]=0;}
	dis[x]=0;q.push(mp(dis[x],x));
	while(q.size()){
		int x=q.top().scd;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>dis[x]+d[i].dist){
				dis[y]=dis[x]+d[i].dist;
				q.push(mp(dis[y],y));
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read()+1;
	for(int i=1;i<=m;i++){int x=read(),y=read(),z=read();Add(x,y,z);Add(y,x,z);}
	m=read();
	for(int i=1;i<=m;i++){int x=read(),y=read();sta[y]|=(1<<(x-2));}
	for(int i=1;i<=K;i++)Dijkstra(i,dis[i]);
	if(K==1){printf("%d",dis[1][n]);return 0;}
	int Sta=(1<<(K-1))-1,t=0,Ans=inf;
	for(int S=1;S<=Sta;S++){int num=__builtin_popcount(S);id[S]=++tot[num];G[num].push_back(S);}
	for(int k=1;k<K;k++){
		t^=1;
		for(auto S:G[k]){
			for(int i=2;i<=K;i++){
				f[i][id[S]][t]=inf;
				if(((S>>(i-2))&1)&&Belong(sta[i],S)){
					if(__builtin_popcount(S)==1)f[i][id[S]][t]=dis[1][i];
					else{
						for(int j=2;j<=K;j++){
							if(((S>>(j-2))&1)&&i!=j){
								f[i][id[S]][t]=min(f[i][id[S]][t],f[j][id[S^(1<<(i-2))]][t^1]+dis[i][j]);
							}
						}
					}
					if(S==Sta)Ans=min(Ans,f[i][id[S]][t]+dis[i][n]);
				}
			}
		}
	}
	printf("%d",Ans);
	return 0;
}