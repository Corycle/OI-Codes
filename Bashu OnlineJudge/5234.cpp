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
#define pii pair<ll,int>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const ll inf=1e18;
const int M=1e5+5;
const int N=2e3+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,t1,t2,cnt;
int a[N],h[N],vis[N],p1[N][N],p2[N][N];
ll b[N],dis1[N],dis2[N],num[N][N],sum[N][N],f[2][N][N];
struct edge{int to,next,dist;}d[M*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
}
void Dijkstra(int s,int &tot,ll dis[]){
	for(int i=1;i<=n;i++){dis[i]=inf;vis[i]=0;}
	priority_queue<pii,vector<pii>,greater<pii> >q;
	q.push(mp(0,s));dis[s]=0;
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
	for(int i=1;i<=n;i++)b[i]=dis[i];
	sort(b+1,b+n+1);tot=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)dis[i]=lower_bound(b+1,b+tot+1,dis[i])-b;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();S=read();T=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	Dijkstra(S,t1,dis1);
	Dijkstra(T,t2,dis2);
	for(int i=1;i<=n;i++){
		num[dis1[i]][dis2[i]]++;
		sum[dis1[i]][dis2[i]]+=a[i];
	}
	for(int i=t1;i>=1;i--){
		for(int j=t2;j>=1;j--){
			sum[i][j]+=sum[i+1][j]+sum[i][j+1]-sum[i+1][j+1];
			if(num[i][j]){p1[i][j]=i;p2[i][j]=j;}
			else{
				p1[i][j]=min(i==t1?t1:p1[i+1][j],j==t2?t1:p1[i][j+1]);
				p2[i][j]=min(i==t1?t2:p2[i+1][j],j==t2?t2:p2[i][j+1]);
			}
			f[0][i][j]=sum[i][j]-f[1][p1[i][j]+1][j];
			f[1][i][j]=sum[i][j]-f[0][i][p2[i][j]+1];
			if(i==1&&j==1)break;
			f[0][i][j]=min(f[0][i][j],f[0][i][j+1]);
			f[1][i][j]=min(f[1][i][j],f[1][i+1][j]);
		}
	}
	ll A=f[0][1][1],B=sum[1][1]-f[0][1][1];
	if(A<B)puts("Cry");
	if(A==B)puts("Flowers");
	if(A>B)puts("Break a heart");
	return 0;
}