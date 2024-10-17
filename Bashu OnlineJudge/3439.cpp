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
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
const int M=17;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int a[N],h[N],fa[N],p[N][M],num[N],Ans[N],dep[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
struct Node{int c,t,id;};
vector<Node>F[N];
void DFS(int x,int depth){
	dep[x]=depth;p[x][0]=fa[x];for(int i=1;i<M;i++)p[x][i]=p[p[x][i-1]][i-1];
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y==fa[x])continue;fa[y]=x;DFS(y,depth+1);}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	return p[x][0];
}
void Solve(int x){
	num[a[x]]++;
	for(auto tmp:F[x])Ans[tmp.id]+=num[tmp.c]*tmp.t;
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y!=fa[x])Solve(y);}
	num[a[x]]--;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	DFS(1,1);
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),c=read(),z=LCA(x,y);
		F[x].push_back((Node){c,1,i});
		F[y].push_back((Node){c,1,i});
		F[z].push_back((Node){c,-1,i});
		F[fa[z]].push_back((Node){c,-1,i});
	}
	Solve(1);
	for(int i=1;i<=m;i++)printf("%d",(Ans[i]>0));
	return 0;
}
