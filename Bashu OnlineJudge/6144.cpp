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
const int M=200005;
const int N=3005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,num,cnt=1;
int h[N],a[N],dis[N],vis[M],prime[M];
struct edge{int to,next,flow;}d[M*100];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
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
			maxx-=dlt;ans+=dlt;
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
void Prepare(int maxn){
	for(int i=2;i<=maxn;i++){
		if(!vis[i])prime[++num]=i;
		for(int j=1;j<=num&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int main(){
//	freopen("prime.in","r",stdin);
//	freopen("prime.out","w",stdout);
	Prepare(2e5);n=read();
	int num=1,S=n+1,T=n+2;
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	while(a[num+1]==1)num++;
	for(int i=num;i<=n;i++){
		if(a[i]&1)Add(S,i,1);
		else Add(i,T,1);
		for(int j=1;j<i;j++){
			if(!vis[a[i]+a[j]]){
				if(a[i]&1)Add(i,j,inf);
				else Add(j,i,inf);
			}
		}
	}
	printf("%d",n-num+1-Dinic(S,T));
	return 0;
}