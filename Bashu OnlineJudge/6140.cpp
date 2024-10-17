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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Flow,Cost,tot,cnt=1;
int A[N],B[N],a[N][N],b[N][N];
int h[N],H[N],t[N],vis[N],dis[N];
struct edge{int to,next,flow,cost;}d[N*N];
struct Route{int s,t,d;}Q[N];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	for(int i=1;i<=tot;i++){vis[i]=0;dis[i]=inf;}
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return dis[t]!=inf;
}
int DFS(int x,int maxx,int t){
	int ans=0;
	if(x==t||!maxx)return maxx;
	vis[x]=1;
	for(int &i=H[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&!vis[y]&&dis[y]==dis[x]+d[i].cost){
			int dlt=DFS(y,min(d[i].flow,maxx),t);
			if(!dlt)dis[y]=-inf;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxx-=dlt;ans+=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
void ZKW(int s,int t){
	Flow=Cost=0;
	while(SPFA(s,t)){
		for(int i=1;i<=tot;i++){H[i]=h[i];vis[i]=0;}
		int dlt=DFS(s,inf,t);Flow+=dlt;Cost+=dlt*dis[t];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	int S=++tot,T=++tot;
	for(int i=1;i<=m;i++)A[i]=++tot;
	for(int i=1;i<=m;i++)B[i]=++tot;
	for(int i=1;i<=n;i++)t[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=b[i][j]=read();
			if(i!=j)a[i][j]+=t[i];
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}
	for(int i=1;i<=m;i++){
		Q[i].s=read();Q[i].t=read();Q[i].d=read();
		Add(S,A[i],1,0);Add(B[i],T,1,0);Add(S,B[i],1,1);
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			if(i==j)continue;
			int st1=Q[i].s,ed1=Q[i].t,t1=Q[i].d;
			int st2=Q[j].s,ed2=Q[j].t,t2=Q[j].d;
			if(t1+b[st1][ed1]+a[ed1][st2]+t[st2]<=t2){
				Add(A[i],B[j],1,0);
			}
		}
	}
	ZKW(S,T);
	printf("%d",Cost);
	return 0;
}