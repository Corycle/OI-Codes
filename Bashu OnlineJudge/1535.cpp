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
double a[N][N];
int n,tot,cnt=1;
int A[N],B[N],h[N],down[N],dis[N];
struct edge{int to,next,flow;}d[N*N];
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
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%lf",&a[i][j]);
		}
	}
	int S=++tot,T=++tot;
	int s=++tot,t=++tot;
	for(int i=1;i<n;i++)A[i]=++tot;
	for(int i=1;i<n;i++)B[i]=++tot;
	for(int i=1;i<n;i++){
		if(a[i][n]!=(int)(a[i][n]))Add(s,A[i],1);
		down[s]-=(int)(a[i][n]);
		down[A[i]]+=(int)(a[i][n]);
	}
	for(int i=1;i<n;i++){
		if(a[n][i]!=(int)(a[n][i]))Add(B[i],t,1);
		down[t]+=(int)(a[n][i]);
		down[B[i]]-=(int)(a[n][i]);
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<n;j++){
			if(a[i][j]!=(int)(a[i][j]))Add(A[i],B[j],1);
			down[A[i]]-=(int)(a[i][j]);
			down[B[j]]+=(int)(a[i][j]);
		}
	}
	int id=cnt,sum=0;
	for(int i=s;i<=tot;i++){
		if(down[i]>0){
			sum+=down[i];
			Add(S,i,down[i]);
		}
		if(down[i]<0)Add(i,T,-down[i]);
	}
	Add(t,s,inf);
	if(Dinic(S,T)!=sum)printf("No");
	else{
		sum=d[cnt].flow;
		for(int i=id+1;i<=cnt;i++)d[i].flow=0;
		printf("%d",(sum+Dinic(s,t))*3);
	}
	return 0;
}