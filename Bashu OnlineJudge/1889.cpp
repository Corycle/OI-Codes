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
const int N=10005;
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,tot,cnt=1;
int a[M][M],num1[N],num2[N];
int h[N],A[N],B[N],L[N],C[N],dis[N];
struct edge{int to,next,flow;}d[N*100];
void Add(int x,int y,int z){
	if(z<0){printf("JIONG!");exit(0);}
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
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++)L[i]=read();
	for(int i=1;i<=m;i++)C[i]=read();
	for(int i=1;i<=K;i++){
		int x=read(),y=read();
		a[x][y]=1;
	}
	int S=++tot,T=++tot;
	for(int i=1;i<=n;i++)A[i]=++tot;
	for(int i=1;i<=m;i++)B[i]=++tot;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j])continue;
			Add(A[i],B[j],1);
			num1[i]++;num2[j]++;
		}
	}
	for(int i=1;i<=n;i++)Add(S,A[i],num1[i]-L[i]);
	for(int i=1;i<=m;i++)Add(B[i],T,num2[i]-C[i]);
	printf("%d",n*m-K-Dinic(S,T));
	return 0;
}