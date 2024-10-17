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
const int Inv2=500000004;
const int Inv3=333333336;
const int Mod=1000000007;
const int N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,tot;
ll w[N],g1[N],g2[N],sp1[N],sp2[N];
int id1[N],id2[N],vis[N],prime[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int id(ll x){return x<=m?id1[x]:id2[n/x];}
void Prepare(int maxn){
	vis[1]=1;
	for(int i=1;i<=maxn;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			sp1[cnt]=mod(sp1[cnt-1]+i);
			sp2[cnt]=mod(sp2[cnt-1]+1ll*i*i%Mod);
		}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int F(int x){return 1ll*x*(x-1)%Mod;}
int S(ll x,int y){
	if(prime[y]>=x)return 0;
	int k=id(x);
	int ans=mod(mod(g2[k]-g1[k]+Mod)-mod(sp2[y]-sp1[y]+Mod)+Mod);
	for(int i=y+1;i<=cnt&&1ll*prime[i]*prime[i]<=x;i++){
		ll Pe=prime[i];
		for(int e=1;Pe<=x;e++,Pe=Pe*prime[i]){
			ans=mod(ans+1ll*F(Pe%Mod)*mod(S(x/Pe,i)+(e!=1))%Mod);
		}
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=sqrt(n);Prepare(m);
	for(ll i=1,j=0;i<=n;i=j+1){
		j=n/(n/i);
		w[++tot]=n/i;
		if(n/i<=m)id1[n/i]=tot;
		else id2[n/(n/i)]=tot;
		int x=w[tot]%Mod;
		g1[tot]=mod(1ll*x*(x+1)%Mod*Inv2%Mod-1+Mod);
		g2[tot]=mod(1ll*x*(x+1)%Mod*Inv2%Mod*(2*x+1)%Mod*Inv3%Mod-1+Mod);
	}
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=tot&&1ll*prime[i]*prime[i]<=w[j];j++){
			int k=id(w[j]/prime[i]);
			g1[j]=mod(g1[j]-1ll*mod(g1[k]-sp1[i-1]+Mod)*prime[i]%Mod+Mod);
			g2[j]=mod(g2[j]-1ll*mod(g2[k]-sp2[i-1]+Mod)*prime[i]%Mod*prime[i]%Mod+Mod);
		}
	}
	printf("%d",mod(S(n,0)+1));
	return 0;
}