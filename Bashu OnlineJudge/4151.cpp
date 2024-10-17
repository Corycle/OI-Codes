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
int n,m,cnt=1;
int A[M][M],B[M][M],C[M][M],h[N],dis[N];
struct edge{int to,next,flow;}d[N*10];
int id(int x,int y){return (x-1)*m+y;}
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
	n=read();m=read();
	int S=n*m+1,T=n*m+2,ans=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)A[i][j]=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)B[i][j]=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)C[i][j]=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(((i+j)&1)==0){Add(S,id(i,j),A[i][j]);Add(id(i,j),T,B[i][j]);}//白 
			if(((i+j)&1)==1){Add(S,id(i,j),B[i][j]);Add(id(i,j),T,A[i][j]);}//黑 
			if(i!=1){Add(id(i,j),id(i-1,j),C[i][j]);Add(id(i-1,j),id(i,j),C[i][j]);}
			if(j!=1){Add(id(i,j),id(i,j-1),C[i][j]);Add(id(i,j-1),id(i,j),C[i][j]);}
			if(i!=n){Add(id(i,j),id(i+1,j),C[i][j]);Add(id(i+1,j),id(i,j),C[i][j]);}
			if(j!=m){Add(id(i,j),id(i,j+1),C[i][j]);Add(id(i,j+1),id(i,j),C[i][j]);}
			ans+=A[i][j]+B[i][j]+C[i][j]*((i!=1)+(j!=1)+(i!=n)+(j!=m));
		}
	}
	printf("%d\n",ans-Dinic(S,T));
	return 0;
}