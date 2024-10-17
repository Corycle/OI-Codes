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
const int Mod=1e9+21;
const int N=1e5+5;
const int M=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans,f[N][M],g[M];
vector<int>F[N],G[N];
int n,m,K,cnt,tot,top,scc;
int a[N],b[N],h[N],st[N],dfn[N],low[N],vis[N],deg[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Tarjan(int x){
	dfn[x]=low[x]=++tot;st[++top]=x;vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!dfn[y]){Tarjan(y);low[x]=min(low[x],low[y]);}
		else if(vis[y])low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		int k=0;scc++;
		do{k=st[top--];vis[k]=0;b[k]=scc;F[scc].push_back(a[k]);}while(k!=x);
	}
}
void Update(int x){
	int num=F[x].size();
	sort(F[x].begin(),F[x].end());
	for(int i=0;i<=K;i++)g[i]=f[x][i];
	for(int i=0;i<num&&i<=K;i++){
		ll tmp=1ll*(num-i)*F[x][i];
		for(int j=K;j>=i;j--)f[x][j]=max(f[x][j],g[j-i]+tmp);
	}
	for(int i=0;i<=K;i++)Ans=max(Ans,f[x][i]);
}
void Solve(){
	queue<int>q;
	for(int i=1;i<=scc;i++)if(!deg[i])q.push(i);
	while(q.size()){
		int x=q.front();q.pop();Update(x);
		int num=G[x].size();
		for(int i=0;i<num;i++){
			int y=G[x][i];
			if(!(--deg[y]))q.push(y);
			for(int j=0;j<=K;j++)f[y][j]=max(f[y][j],f[x][j]);
		}
	}
}
int main(){
//	freopen("tax.in","r",stdin);
//	freopen("tax.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();m=read();K=read();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=m;i++){int x=read(),y=read();Add(x,y);}
		for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i);
		for(int x=1;x<=n;x++){
			for(int i=h[x];i;i=d[i].next){
				int y=d[i].to;
				if(b[x]!=b[y]){G[b[x]].push_back(b[y]);deg[b[y]]++;}
			}
		}
		Solve();
		printf("%lld\n",Ans%Mod);
		for(int i=1;i<=n;i++)h[i]=b[i]=dfn[i]=low[i]=0;
		for(int i=1;i<=scc;i++){
			for(int j=0;j<=K;j++)f[i][j]=0;
			deg[i]=0;G[i].clear();F[i].clear();
		}
		Ans=cnt=tot=scc=0;
	}
	return 0;
}