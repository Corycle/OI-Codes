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
const int N=905;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt=1;
int h[N],down[N],dis[N];
int id[35][35],a[35][35];
struct edge{
	int to,next,flow;
}d[N*50];
void Add(int x,int y,int f){
	d[++cnt]=(edge){y,h[x],f};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	queue<int>q;
	memset(dis,-1,sizeof(dis));
	q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]==-1&&d[i].flow){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	int ans=0,dlt=0;
	if(x==t||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){
	int ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	int tot=0,ans=0;
	int S=0,T=n*m+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			id[i][j]=++tot;
			ans+=a[i][j];
			if((i+j)%2==0)Add(S,id[i][j],a[i][j]);
			if((i+j)%2==1)Add(id[i][j],T,a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if((i+j)%2==0){
				if(j!=1)Add(id[i][j],id[i][j-1],inf);
				if(i!=1)Add(id[i][j],id[i-1][j],inf);
				if(j!=m)Add(id[i][j],id[i][j+1],inf);
				if(i!=n)Add(id[i][j],id[i+1][j],inf);
			}
		}
	}
	printf("%d",ans-Dinic(S,T));
	return 0;
}