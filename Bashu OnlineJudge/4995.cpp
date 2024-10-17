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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt1,cnt2,cnt;
int h[N],h1[N],h2[N],dis[N],val[N];
struct Edge{int to,next;}e1[N],e2[N];
struct edge{int to,next,flow;}d[N*N];
void Addedge1(int x,int y){
	e1[++cnt1]=(Edge){y,h1[x]};h1[x]=cnt1;
	e1[++cnt1]=(Edge){x,h1[y]};h1[y]=cnt1;
}
void Addedge2(int x,int y){
	e2[++cnt2]=(Edge){y,h2[x]};h2[x]=cnt2;
	e2[++cnt2]=(Edge){x,h2[y]};h2[y]=cnt2;
}
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
void Prepare(){
	cnt1=cnt2=0;
	memset(h1,0,sizeof(h1));
	memset(h2,0,sizeof(h2));
}
bool BFS(int s,int t){
	memset(dis,-1,sizeof(dis));
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	int ans=0;
	if(x==t||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(d[i].flow,maxx),t);
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
void DFS1(int x,int fa){
	for(int i=h1[x];i;i=e1[i].next){
		int y=e1[i].to;
		if(y==fa)continue;
		Add(y,x,inf);
		DFS1(y,x);
	}
}
void DFS2(int x,int fa){
	for(int i=h2[x];i;i=e2[i].next){
		int y=e2[i].to;
		if(y==fa)continue;
		Add(y,x,inf);
		DFS2(y,x);
	}
}
int Solve(int x){
	int ans=0;cnt=1;
	int S=n+1,T=n+2;
	memset(h,0,sizeof(h));
	DFS1(x,0);DFS2(x,0);
	for(int i=1;i<=n;i++){
		if(val[i]>=0){
			ans+=val[i];
			Add(S,i,val[i]);
		}
		else Add(i,T,-val[i]);
	}
	return ans-Dinic(S,T);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		int ans=0;n=read();Prepare();
		for(int i=1;i<=n;i++)val[i]=read();
		for(int i=1;i<n;i++)Addedge1(read(),read());
		for(int i=1;i<n;i++)Addedge2(read(),read());
		for(int i=1;i<=n;i++)ans=max(ans,Solve(i));
		printf("%d\n",ans);
	}
	return 0;
}