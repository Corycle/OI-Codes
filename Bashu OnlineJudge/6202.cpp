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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=300005;
const int P=3005;
const int M=12;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,Flow,Cost,cnt=1;
int h[N],H[N],dis[N],vis[N];
int L[P][M],R[P][M],A[P][M],B[P][M];
struct edge{int to,next,flow,cost;}d[N*20];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	for(int i=1;i<=tot;i++){
		vis[i]=0;dis[i]=inf;
	}
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return dis[t]!=inf;
}
int DFS(int x,int maxx,int t){
	int ans=0;
	if(x==t||!maxx)return maxx;
	vis[x]=1;
	for(int &i=H[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&!vis[y]&&dis[y]==dis[x]+d[i].cost){
			int dlt=DFS(y,min(d[i].flow,maxx),t);
			if(!dlt)dis[y]=-inf;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxx-=dlt;ans+=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
void ZKW(int s,int t){
	Flow=Cost=0;
	while(SPFA(s,t)){
		for(int i=1;i<=tot;i++){
			H[i]=h[i];vis[i]=0;
		}
		int dlt=DFS(s,inf,t);
		Flow+=dlt;
		Cost+=dlt*dis[t];
	}
}
struct Segment_Tree{
	int t1[P*4],t2[P*4];
	void Build(int pos,int p,int l,int r){
		if(l==r){
			t1[p]=B[l][pos];
			t2[p]=B[l][pos];
			return;
		}
		int mid=(l+r)>>1;
		t1[p]=++tot;t2[p]=++tot;
		Build(pos,lson);Build(pos,rson);
		Add(t1[p],t1[p<<1],inf,(r-mid)*2);
		Add(t1[p],t1[p<<1|1],inf,0);
		Add(t2[p],t2[p<<1],inf,0);
		Add(t2[p],t2[p<<1|1],inf,(mid-l+1)*2);
	}
	void Update1(int x,int y,int id,int pos,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			Add(id,t1[p],inf,(pos-r)*2);
			return;
		}
		int mid=(l+r)>>1;
		Update1(x,y,id,pos,lson);
		Update1(x,y,id,pos,rson);
	}
	void Update2(int x,int y,int id,int pos,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			Add(id,t2[p],inf,(l-pos)*2);
			return;
		}
		int mid=(l+r)>>1;
		Update2(x,y,id,pos,lson);
		Update2(x,y,id,pos,rson);
	}
}tree[M];
int main(){
//	freopen("desk.in","r",stdin);
//	freopen("desk.out","w",stdout);
	n=read();m=read();
	int S=++tot,T=++tot;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)A[i][j]=++tot;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)B[i][j]=++tot;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)L[i][j]=read()+1;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)R[i][j]=read()+1;
	for(int i=1;i<=m;i++)tree[i].Build(i,1,1,n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)Add(S,A[i][j],1,0);
		for(int j=1;j<=m;j++)Add(B[i][j],T,1,0);
		for(int j=1;j<m;j++)Add(B[i][j],B[i][j+1],inf,1);
		for(int j=m;j>1;j--)Add(B[i][j],B[i][j-1],inf,1);
		Add(B[i][m],B[i][1],inf,1);
		Add(B[i][1],B[i][m],inf,1);
		for(int j=1;j<=m;j++){
			if(L[i][j]<=i)tree[j].Update1(L[i][j],min(R[i][j],i),A[i][j],i,1,1,n);
			if(R[i][j]>=i)tree[j].Update2(max(i,L[i][j]),R[i][j],A[i][j],i,1,1,n);
		}
	}
	ZKW(S,T);
	if(Flow!=n*m)printf("no solution");
	else printf("%d",Cost);
	return 0;
}