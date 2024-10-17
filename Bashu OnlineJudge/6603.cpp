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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G1[N],G2[N];
int n,m,cnt,Ans,a[N],h[N],dis[N];
struct edge{int to,next,flow;}d[N*N];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
void Add1(int x,int y){G1[x].push_back(y);G1[y].push_back(x);}
void Add2(int x,int y){G2[x].push_back(y);G2[y].push_back(x);}
void DFS1(int x,int fa){int num=G1[x].size();if(fa)Add(x,fa,inf);for(int i=0;i<num;i++)if(G1[x][i]!=fa)DFS1(G1[x][i],x);}
void DFS2(int x,int fa){int num=G2[x].size();if(fa)Add(x,fa,inf);for(int i=0;i<num;i++)if(G2[x][i]!=fa)DFS2(G2[x][i],x);}
bool BFS(int s,int t){
	for(int i=1;i<=t;i++)dis[i]=-1;
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
int DFS(int x,int maxn,int t){
	if(x==t||!maxn)return maxn;
	int ans=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(maxn,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxn-=dlt;ans+=dlt;
			if(!maxn)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){int ans=0;while(BFS(s,t))ans+=DFS(s,inf,t);return ans;}
void Solve(int x){
	int S=n+1,T=n+2,sum=0;cnt=1;
	for(int i=1;i<=T;i++)h[i]=0;
	DFS1(x,0);DFS2(x,0);
	for(int i=1;i<=n;i++){
		if(a[i]>0)Add(S,i,a[i]),sum+=a[i];
		if(a[i]<0)Add(i,T,-a[i]);
	}
	Ans=max(Ans,sum-Dinic(S,T));
}
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++)Add1(read()+1,read()+1);
	for(int i=1;i<n;i++)Add2(read()+1,read()+1);
	for(int i=1;i<=n;i++)Solve(i);
	printf("%d",Ans);
	return 0;
}