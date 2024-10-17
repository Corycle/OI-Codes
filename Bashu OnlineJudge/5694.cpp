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
const int M=600005;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int m,c,n1,n2,tot,cnt=1;
int A[N],B[N],C[N],D[N];
int h[N],H[N],dis[N],vis[N];
struct edge{int to,next,flow;}d[M];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	for(int i=1;i<=tot;i++)dis[i]=-1;
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
	if(x==t||!maxx)return maxx;
	int ans=0;
	for(int &i=H[x];i;i=d[i].next){
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
	while(BFS(s,t)){
		for(int i=1;i<=tot;i++)H[i]=h[i];
		ans+=DFS(s,inf,t);
	}
	return ans;
}
void dfs(int x){
	vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&!vis[y])dfs(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();c=read();
	int S=++tot,T=++tot;
	for(int i=1;i<=m;i++)C[i]=++tot;
	for(int i=1;i<=c;i++)D[i]=++tot;
	n1=read();
	for(int i=1;i<=n1;i++){
		A[i]=++tot;
		Add(S,A[i],1);
		Add(A[i],C[read()],1);
		Add(A[i],D[read()],1);
	}
	n2=read();
	for(int i=1;i<=n2;i++){
		B[i]=++tot;
		Add(B[i],T,1);
		Add(C[read()],B[i],1);
		Add(D[read()],B[i],1);
	}
	Dinic(S,T);dfs(S);
	for(int i=1;i<=n1;i++)printf("%d\n",vis[A[i]]^1);
	return 0;
}