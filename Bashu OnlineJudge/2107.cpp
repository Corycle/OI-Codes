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
const int Mod=1e9+7;
const int N=2e5+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,cnt,tot,top,Ans;
int a[N],h[N],f[N],g[N],t[N],fa[N],st[N],mu[N],phi[N];
int dep[N],pos[N],dfn[N],vis[N],sum[N],prime[N],p[N][M];
struct edge{int to,next;}d[N*2];
int mod(int x){return x>=Mod?x-Mod:x;}
bool cmp(int x,int y){return dfn[x]<dfn[y];}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(int maxn){
	mu[1]=phi[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;phi[i]=i-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]){
				mu[i*prime[j]]=-mu[i];
				phi[i*prime[j]]=1ll*phi[i]*phi[prime[j]]%Mod;
			}
			else{
				mu[i*prime[j]]=0;
				phi[i*prime[j]]=1ll*phi[i]*prime[j]%Mod;
				break;
			}
		}
	}
	for(int i=1;i<=maxn;i++){mu[i]=mod(Mod+mu[i]);vis[i]=0;}cnt=0;
}
void DFS(int x,int depth){
	dep[x]=depth;p[x][0]=fa[x];dfn[x]=++tot;
	for(int i=1;i<M;i++)p[x][i]=p[p[x][i-1]][i-1];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,depth+1);
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	}
	return p[x][0];
}
int Build(){
	sort(t+1,t+m+1,cmp);
	st[top=1]=t[1];
	for(int i=2;i<=m;i++){
		int lca=LCA(t[i],st[top]);
		while(top>=2&&dep[st[top-1]]>=dep[lca]){G[st[top-1]].push_back(st[top]);top--;}
		if(st[top]!=lca){G[lca].push_back(st[top]);st[top]=lca;}
		st[++top]=t[i];
	}
	while(top>=2){G[st[top-1]].push_back(st[top]);top--;}
	return st[1];
}
void Solve(int x){
	sum[x]=vis[x]*phi[a[x]];
	Ans=mod(Ans-1ll*sum[x]*sum[x]%Mod*dep[x]%Mod+Mod);
	for(auto y:G[x]){
		Solve(y);
		Ans=mod(Ans-2ll*sum[x]*sum[y]%Mod*dep[x]%Mod+Mod);
		sum[x]=mod(sum[x]+sum[y]);
	}
}
void Clear(int x){
	for(auto y:G[x])Clear(y);
	G[x].clear();sum[x]=vis[x]=0;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare(n);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)pos[a[i]]=i;
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,1);
	for(int x=1;x<=n;x++){
		int sum1=0,sum2=0;Ans=0;m=0;
		for(int i=x;i<=n;i+=x)t[++m]=pos[i];
		for(int i=1;i<=m;i++){
			vis[t[i]]=1;
			sum1=mod(sum1+phi[a[t[i]]]);
			sum2=mod(sum2+1ll*phi[a[t[i]]]*dep[t[i]]%Mod);
		}
		int root=Build();
		Solve(root);
		f[x]=mod(2ll*sum1*sum2%Mod+mod(Ans+Ans));
		Clear(root);
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=i){
			g[i]=mod(g[i]+1ll*f[j]*mu[j/i]%Mod);
		}
	}
	int Ans=0;
	for(int i=1;i<=n;i++){
		Ans=mod(Ans+1ll*i*Pow(phi[i],Mod-2)%Mod*g[i]%Mod);
	}
	Ans=1ll*Ans*Pow(1ll*n*(n-1)%Mod,Mod-2)%Mod;
	printf("%d",Ans);
	return 0;
}