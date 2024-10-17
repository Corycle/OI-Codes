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
#include<unordered_map>
#define ll long long
#define fst first
#define scd second
#define mp make_pair
#define pii pair<int,int>
using namespace std;
const int inf=0x3f3f3f3f;
const int M=1e6+5;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
unordered_map<int,int>F[N];
ll Answer,Ans[N],val[N];
int n,m,cnt,tot,scc,top;
int a[N],h[N],id[N],st[N],dfn[N],low[N],vis[N],son[N],num[M],sum[M];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Addedge(int x,int y){G[x].push_back(y);G[y].push_back(x);}
void Tarjan(int x,int pre){
	dfn[x]=low[x]=++tot;st[++top]=x;
	for(int i=h[x];i;i=d[i].next){
		if(i==(pre^1))continue;
		int y=d[i].to;
		if(!dfn[y]){
			Tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				int k=0;scc++;Addedge(scc,x);
				do{k=st[top--];Addedge(scc,k);}while(k!=y);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
void DFS(int x,int fa){vis[x]=1;if(x<=n)num[a[x]]++;for(auto y:G[x])if(y!=fa)DFS(y,x);}
void Update(int x,int c,int t){
	int &tmp=F[id[x]][c];
	val[x]-=1ll*tmp*(num[c]-tmp);
	tmp+=t;
	val[x]+=1ll*tmp*(num[c]-tmp);
	Ans[x]+=1ll*t*(num[c]-tmp);
}
void Solve(int x,int fa){
	for(auto y:G[x])if(y!=fa){Solve(y,x);if(F[id[y]].size()>F[id[son[x]]].size())son[x]=y;}
	if(!son[x])id[x]=++tot;
	else{id[x]=id[son[x]];val[x]=val[son[x]];Ans[x]=val[x];}
	if(x<=n)Update(x,a[x],1);
	for(auto y:G[x]){
		if(y==fa||y==son[x])continue;
		for(auto tmp:F[id[y]])Update(x,tmp.fst,tmp.scd);
	}
}
int main(){
//	freopen("pairs.in","r",stdin);
//	freopen("pairs.out","w",stdout);
	n=read();m=read();scc=n;cnt=1;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i,0);
	tot=0;
	for(int x=1;x<=n;x++){
		if(vis[x])continue;
		DFS(x,0);Solve(x,0);
		for(auto tmp:F[id[x]]){
			Answer+=1ll*sum[tmp.fst]*tmp.scd;
			sum[tmp.fst]+=tmp.scd;
			num[tmp.fst]=0;
		}
	}
	for(int i=1;i<=n;i++)printf("%lld\n",Answer+Ans[i]);
	return 0;
}