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
const ll inf=0x3f3f3f3f;
const ll Mod=1e9+7;
const ll M=100005;
const ll N=305;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,Ans;
vector<ll>V[N];
ll Fac[M],Inv[M],Sum[N];
ll f[N],inv[N],a[N][N],b[N][N];
ll g[N][N],pos[N][N],sum[N][N];
void Prepare(ll maxn){
	Fac[0]=Fac[1]=Inv[0]=Inv[1]=1;
	for(ll i=2;i<=maxn;i++)Fac[i]=Fac[i-1]*i%Mod;
	for(ll i=2;i<=maxn;i++)Inv[i]=Inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(ll i=2;i<=maxn;i++)Inv[i]=Inv[i-1]*Inv[i]%Mod;
}
void Solve(ll l,ll r){
	for(ll i=1;i<=n;i++){
		ll num=V[i].size();
		for(ll j=0;j<num;j++){
			ll x=V[i][j];
			if(pos[i][r]<pos[x][r]){
				swap(V[i][j],V[i][num-1]);
				V[i].pop_back();num--;j--;
			}
			else{
				g[i][x]=g[i][x]*Inv[pos[i][r]-pos[x][r]-1]%Mod;
			}
		}
	}
	for(ll i=1;i<=n;i++){
		Sum[a[r][i]]+=i-1;
		inv[a[r][i]]=inv[a[r][i]]*Inv[i-1]%Mod;
	}
	memset(f,0,sizeof(f));
	for(ll i=1;i<=n;i++){
		ll p=a[r][i];
		f[p]=Fac[r-l+1]*Fac[Sum[p]]%Mod*inv[p]%Mod;
		ll num=V[p].size();
		for(ll j=0;j<num;j++){
			ll x=V[p][j];
			ll len=Sum[p]-Sum[x]-(r-l+1);
			f[p]=(f[p]-f[x]*Fac[len]%Mod*Fac[r-l+1]%Mod*g[p][x]%Mod+Mod)%Mod;
		}
	}
	Ans=(Ans+f[n]*Inv[r-l+1]%Mod)%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare(N*N);
	m=read();n=read()+1;
	for(ll i=1;i<=m;i++){
		for(ll j=1;j<n;j++){
			pos[a[i][j]=read()][i]=j;
		}
		pos[a[i][n]=n][i]=n;
	}
	for(ll l=1;l<=m;l++){
		for(ll i=1;i<=n;i++){
			V[i].clear();
			inv[i]=1;Sum[i]=0;
			for(ll j=1;j<=n;j++){
				if(i==j)continue;
				V[i].push_back(j);
				g[i][j]=1;
			}
		}
		for(ll r=l;r<=m;r++)Solve(l,r);
	}
	printf("%lld",Ans);
	return 0;
}