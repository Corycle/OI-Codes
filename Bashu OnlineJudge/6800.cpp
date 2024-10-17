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
const ll inf=1e18;
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,cnt=1,h[N],dis[N];
struct edge{int to,next;ll flow;}d[N*8];
void Add(int x,int y,int f){
	d[++cnt]=(edge){y,h[x],f};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	for(int i=1;i<=n;i++)dis[i]=-1;
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
ll DFS(int x,ll maxn,int t){
	if(x==t||!maxn)return maxn;
	ll ans=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			ll dlt=DFS(y,min(maxn,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxn-=dlt;ans+=dlt;
			if(!maxn)return ans;
		}
	}
	return ans;
}
ll Dinic(int s,int t){ll ans=0;while(BFS(s,t))ans+=DFS(s,inf,t);return ans;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();S=read();T=read();
	for(int i=1;i<=m;i++){int x=read(),y=read(),z=read();Add(x,y,z);}
	printf("%lld\n",Dinic(S,T));
	return 0;
}