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
#define pii pair<int,int>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
const int M=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
pii id[N];
int vis[N],dis[N],pre[N];
int h[N],A[N],B[M][M],a[M][M];
int n,m,Flow,Cost,tot,Sum,cnt=1;
struct edge{int to,next,flow,cost;}d[N*10];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
void Build(int x,int y){
	for(int i=1;i<=n;i++){
		Add(A[i],B[x][y],1,a[i][x]*y);
	}
}
bool SPFA(int s,int t){
	for(int i=1;i<=tot;i++){
		vis[i]=0;pre[i]=0;dis[i]=inf;
	}
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;pre[y]=i;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return dis[t]<inf;
}
void Adjust(int s,int t){
	int p=0,dlt=inf;
	for(int i=t;i!=s;i=d[p^1].to){
		p=pre[i];
		dlt=min(dlt,d[p].flow);
	}
	for(int i=t;i!=s;i=d[p^1].to){
		p=pre[i];
		d[p].flow-=dlt;
		d[p^1].flow+=dlt;
	}
	Flow+=dlt;
	Cost+=dlt*dis[t];
	p=d[pre[t]^1].to;
	Build(id[p].first,id[p].second+1);
}
void Edmonds_Karp(int s,int t){
	while(SPFA(s,t))Adjust(s,t);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	int S=++tot,T=++tot;
	for(int i=1;i<=n;i++){
		A[i]=++tot;
		int num=read();
		Add(S,A[i],num,0);
		Sum+=num;
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=Sum;j++){
			B[i][j]=++tot;
			Add(B[i][j],T,1,0);
			id[tot]=make_pair(i,j);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
		}
	}
	for(int i=1;i<=m;i++)Build(i,1);
	while(Flow<Sum){
		Edmonds_Karp(S,T);
	}
	printf("%d",Cost);
	return 0;
}