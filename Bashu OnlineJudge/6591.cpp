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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,scc,tot,top,type;
int h[N],b[N],st[N],dfn[N],low[N],dis[N],vis[N],Gcd[N];
struct edge{int to,next;}d[N*2];
ll gcd(ll a,ll b){return !b?a:gcd(b,a%b);}
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
		do{k=st[top--];b[k]=scc;vis[k]=0;}while(k!=x);
	}
}
void DFS(int x,int dist){
	vis[x]=1;dis[x]=dist;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(b[x]!=b[y])continue;
		if(!vis[y])DFS(y,dist+1);
		else{
			if(!Gcd[b[x]])Gcd[b[x]]=abs(dis[x]-dis[y]+1);
			else Gcd[b[x]]=gcd(Gcd[b[x]],abs(dis[x]-dis[y]+1));
		}
	}
}
namespace Task1{
	const int M=205;
	struct Matrix{
		bool a[M][M];
		void Init(){for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=0;}
		friend Matrix operator*(Matrix A,Matrix B){
			Matrix C;C.Init();
			for(int i=1;i<=n;i++){
				for(int k=1;k<=n;k++){
					if(!A.a[i][k])continue;
					for(int j=1;j<=n;j++){
						C.a[i][j]|=(A.a[i][k]&B.a[k][j]);
					}
				}
			}
			return C;
		}
	}F,Ans,tot;
	void Solve(ll t){
		tot=F;Ans.Init();
		for(int i=1;i<=n;i++)Ans.a[i][i]=1;
		while(t){
			if(t&1)Ans=Ans*tot;
			tot=tot*tot;
			t>>=1;
		}
	}
	bool Check(ll x,ll y){
		Solve(x);Matrix A=Ans;
		Solve(y);Matrix B=Ans;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(A.a[i][j]!=B.a[i][j])return false;
			}
		}
		return true;
	}
	void Main(){
		ll D=Gcd[1];
		for(int i=2;i<=scc;i++)D=D/gcd(D,Gcd[i])*Gcd[i];
		int l=1,r=5e4,K=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(Check(mid,mid+D)){K=mid;r=mid-1;}
			else l=mid+1;
		}
		printf("%d %lld",K,D%Mod);
	}
}
namespace Task2{
	int cnt,vis[N],prime[N],Max[N],pos[N];
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
		for(int i=2;i<=maxn;i++){
			if(!vis[i]){prime[++cnt]=i;pos[i]=cnt;}
			for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
				vis[i*prime[j]]=1;
				if(i%prime[j]==0)break;
			}
		}
	}
	void Divide(int x){
		for(int i=1;i<=cnt&&1ll*prime[i]*prime[i]<=x;i++){
			if(x%prime[i]==0){
				int num=0;
				while(x%prime[i]==0){x/=prime[i];num++;}
				Max[i]=max(Max[i],num);
			}
		}
		if(x!=1)Max[pos[x]]=max(Max[pos[x]],1);
	}
	void Main(){
		int D=1;Prepare(n);
		for(int i=1;i<=scc;i++)Divide(Gcd[i]);
		for(int i=1;i<=cnt;i++)D=1ll*D*Pow(prime[i],Max[i])%Mod;
		printf("%d",D);
	}
}
int main(){
//	freopen("graph.in","r",stdin);
//	freopen("graph.out","w",stdout);
	n=read();m=read();type=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();Add(x,y);
		if(type==1)Task1::F.a[x][y]=1;
	}
	for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i);
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=1;i<=n;i++)if(!vis[i])DFS(i,1);
	for(int i=1;i<=scc;i++)if(!Gcd[i])Gcd[i]=1;
	if(type==1){Task1::Main();return 0;}
	Task2::Main();
	return 0;
}