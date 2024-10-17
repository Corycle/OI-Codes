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
const int N=50005;
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<int,int>ID[N];
int n,m,Flow,Cost,tot,cnt=1;
int h[N],vis[N],dis[N],pre[N];
int A[N],a[M][M],id[M][M];
struct edge{int to,next,flow,cost;}d[N*10];
void Add(int x,int y,int f,int c){
	ID[x][y]=cnt+1;
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
	memset(dis,0x3f,sizeof(dis));
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
}
void Edmonds_Karp(int s,int t){
	while(SPFA(s,t))Adjust(s,t);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	int S=++tot,T=++tot;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=read();
			id[i][j]=++tot;
		}
		A[i]=++tot;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			Add(S,id[i][j],1,0);
			if(a[i][j]==0)Add(id[i][j],A[i],1,0);
			if(a[i][j]==1)Add(id[i][j],A[j],1,0);
			if(a[i][j]==2){
				Add(id[i][j],A[i],1,0);
				Add(id[i][j],A[j],1,0);
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<n;j++){
			Add(A[i],T,1,j);
		}
	}
	Edmonds_Karp(S,T);
	printf("%d\n",n*(n-1)*(n-2)/6-Cost);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)printf("0 ");
			else if(a[i][j]!=2)printf("%d ",a[i][j]);
			else{
				int x=i,y=j;
				if(x>y)swap(x,y);
				printf("%d ",d[ID[id[x][y]][A[i]]].flow);
			}
		}
		printf("\n");
	}
	return 0;
}