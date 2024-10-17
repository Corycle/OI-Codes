#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,ans1,ans2,cnt=1;
int a[N][N],id[N][N],h[N],dis[N],vis[N],pre[N];
struct edge{int to,next,flow,cost;}d[N*N];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
struct cmp{
	bool operator()(int x,int y){
		return dis[x]>dis[y];
	}
};
bool SPFA(int s,int t){
	priority_queue<int,vector<int>,cmp>q;
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
	q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.top();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;pre[y]=i;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	if(dis[t]==inf)return false;
	return true;
}
void Adjust(int s,int t){
	int dlt=inf,p=0;
	for(int i=t;i!=s;i=d[p^1].to){
		p=pre[i];
		dlt=min(dlt,d[p].flow);
	}
	for(int i=t;i!=s;i=d[p^1].to){
		p=pre[i];
		d[p].flow-=dlt;
		d[p^1].flow+=dlt;
	}
	ans1+=dlt;
	ans2+=dlt*dis[t];
}
void Edmonds_Karp(int s,int t){
	while(SPFA(s,t))Adjust(s,t);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	int dlt=n*m;
	int S=dlt*2+1,T=dlt*2+2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();id[i][j]=(i-1)*m+j;
			Add(id[i][j],id[i][j]+dlt,1,a[i][j]);
		}
	}
	int k=read();
	while(k--){
		int sx=read(),sy=read();
		int fx=read(),fy=read();
		Add(id[sx][sy]+dlt,id[fx][fy],1,0);
		Add(id[fx][fy]+dlt,id[sx][sy],1,0);
	}
	k=read();
	for(int i=1;i<=k;i++){
		int x=read(),y=read();
		Add(S,id[x][y],1,0);
	}
	for(int i=1;i<=k;i++){
		int x=read(),y=read();
		Add(id[x][y]+dlt,T,1,0);
	}
	Edmonds_Karp(S,T);
	if(ans1!=k)printf("-1");
	else printf("%d",ans2);
	return 0;
}