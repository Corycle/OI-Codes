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
#define ld long double
#define Com Combinatorics
#define pii pair<ll,ll>
#define mp make_pair
#define fst first
#define scd second
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=11920928955078125ll;
const double eps=1e-10;
const ll M=10005;
const ll N=65;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Mul(ll a,ll b,ll p=Mod){return ((a*b-(ll)((ld)a*b/p+eps)*p)+p)%p;}
ll Pow(ll x,ll y){ll a=1,t=x;while(y){if(y&1)a=Mul(a,t);t=Mul(t,t);y>>=1;}return a;}
namespace Combinatorics{
	const ll S=23;
	ll K,p[S],C[S][S],Tmp[S];
	struct Node{
		ll a[S];
		void Init(ll A=0,ll B=0){memset(a,0,sizeof(a));a[0]=A;a[1]=B;}
		friend Node operator*(Node A,Node B){
			Node C;C.Init();
			for(int i=0;i<S;i++){
				for(int j=0;i+j<S;j++){
					if(A.a[i]&&B.a[j])C.a[i+j]=(C.a[i+j]+Mul(A.a[i],B.a[j]))%Mod;
				}
			}
			return C;
		}
		void Calc(ll k){
			p[0]=1;
			for(int i=1;i<S;i++)p[i]=Mul(p[i-1],k);
			memset(Tmp,0,sizeof(Tmp));
			for(int i=0;i<S;i++){
				for(int j=0;j<=i;j++){
					Tmp[j]=(Tmp[j]+Mul(a[i],Mul(p[i-j],C[i][j])))%Mod;
				}
			}
			memcpy(a,Tmp,sizeof(a));
		}
	}P[M];
	void Init(){
		for(int i=0;i<S;i++){
			C[i][0]=1;
			for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
		}
		P[0].Init(1,0);
		for(int i=1;i<=10000;i++){
			if(i%5){
				Node tmp;tmp.Init(i,1);
				P[i]=P[i-1]*tmp;
			}
			else P[i]=P[i-1];
		}
	}
	Node Fac(ll n){
		if(n<=10000)return P[n];
		ll k=n/10*10;
		Node t1=Fac(k>>1),t2=t1;
		t2.Calc(k>>1);t1=t1*t2;
		for(ll i=k+1;i<=n;i++){
			if(i%5){
				Node tmp;tmp.Init(i,1);
				t1=t1*tmp;
			}
		}
		return t1;
	}
	pii fac(ll n){
		pii ans=mp(Fac(n).a[0],n/5);
		if(n>=5){
			pii tmp=fac(n/5);
			ans.fst=Mul(ans.fst,tmp.fst);
			ans.scd=ans.scd+tmp.scd;
		}
		return ans;
	}
	ll Calc(ll n){
		if(n<K)return 0;
		pii fn=fac(n),fk=fac(K),fnk=fac(n-K);
		fn.scd-=fk.scd+fnk.scd;
		fn.fst=Mul(Mul(fn.fst,Pow(Mul(fk.fst,fnk.fst),Mod/5*4-1)),Pow(5,fn.scd));
		return fn.fst;
	}
}
ll n,m,cnt,tot,Max,Maxval;
ll h[N],w[N],v[N],f[N][M],g[N][M],vis[N];
ll fa[N],dfn[N],sum[N],dis[N][N],flag[N];
struct edge{ll to,next,dist;}d[N*2];
void Add(ll x,ll y,ll z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
void dfs(ll x,ll Fa){
	fa[x]=Fa;
	for(int i=h[x];i;i=d[i].next)if(d[i].to!=Fa)dfs(d[i].to,x);
}
void BFS(ll sx){
	for(int i=1;i<=n;i++)vis[i]=0;
	queue<ll>q;q.push(sx);vis[sx]=1;
	while(q.size()){
		ll x=q.front();q.pop();
		for(int i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(!vis[y]){
				vis[y]=1;q.push(y);
				dis[sx][y]=dis[sx][x]+d[i].dist;
			}
		}
	}
}
void DFS(ll x,ll Fa){
	sum[x]=1;dfn[++tot]=x;
	for(int i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==Fa||!flag[y])continue;
		DFS(y,x);sum[x]+=sum[y];
	}
}
pii DP(ll x,ll y){
	tot=0;DFS(x,0);
	for(int i=0;i<=m;i++){f[tot+1][i]=0;g[tot+1][i]=1;}
	for(int i=tot;i>=1;i--){
		ll p=dfn[i];
		for(int j=0;j<=m;j++){
			if(p==y){
				if(j-w[p]<0)f[i][j]=g[i][j]=0;
				else{
					f[i][j]=f[i+1][j-w[p]]+v[p];
					g[i][j]=g[i+1][j-w[p]];
				}
			}
			else{
				f[i][j]=f[i+sum[p]][j];
				g[i][j]=g[i+sum[p]][j];
				if(j-w[p]>=0){
					if(f[i+sum[p]][j]==f[i+1][j-w[p]]+v[p])g[i][j]+=g[i+1][j-w[p]];
					if(f[i+sum[p]][j]<f[i+1][j-w[p]]+v[p]){
						f[i][j]=f[i+1][j-w[p]]+v[p];
						g[i][j]=g[i+1][j-w[p]];
					}
				}
			}
		}
	}
	return mp(f[1][m],g[1][m]);
}
ll Solve(ll x,ll y){
	for(int i=1;i<=n;i++){
		flag[i]=(dis[x][i]*v[i]<=Max&&dis[y][i]*v[i]<=Max);
	}
	if(!flag[x]||!flag[y])return 0;
	pii tmp=DP(x,y);
//	cout<<"Solve: "<<x<<" "<<y<<": "<<endl;
//	cout<<tmp.fst<<" "<<tmp.scd<<" "<<Com::Calc(tmp.scd)<<endl;
	return (tmp.fst==Maxval?Com::Calc(tmp.scd):0);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	Com::K=read();Max=read();Com::Init();
	for(int i=1;i<=n;i++)w[i]=read();
	for(int i=1;i<=n;i++)v[i]=read();
	for(int i=1;i<n;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	ll Ans=0;dfs(1,0);
	for(int i=1;i<=n;i++)BFS(i);
	for(int i=0;i<=n;i++)flag[i]=1;
	for(int i=1;i<=n;i++)Maxval=max(Maxval,DP(i,0).fst);
//	for(int i=1;i<=n;i++)cout<<fa[i]<<" ";cout<<endl;
	for(int i=1;i<=n;i++){
		Ans=(Ans+Solve(i,0)-(fa[i]?Solve(i,fa[i]):0)+Mod)%Mod;
	}
	printf("%lld",Ans);
	return 0;
}