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
const int M=2e7+5;
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bool vis[M];
int n,m,tot,cnt,prime[M/10],phi[M],Mod[30],a[N];
struct BIT{
	ll c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	ll Ask(int x){ll ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree;
ll Pow(ll x,ll y,ll mod){
	ll ans=1;if(x>mod)x=x%mod+mod;
	while(y){
		if(y&1){ans=ans*x;if(ans>mod)ans=ans%mod+mod;}
		x=x*x;if(x>mod)x=x%mod+mod;y>>=1;
	}
	return ans;
}
void Prepare(){
	phi[1]=1;
	for(int i=2;i<M;i++){
		if(!vis[i]){prime[++cnt]=i;phi[i]=i-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<M;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])phi[i*prime[j]]=phi[i]*phi[prime[j]];
			else{phi[i*prime[j]]=phi[i]*prime[j];break;}
		}
	}
}
int Solve(int l,int r,int t){
	ll val=tree.Ask(l);
	if(l==r||t==tot)return val<Mod[t]?val:val%Mod[t]+Mod[t];
	return Pow(val,Solve(l+1,r,t+1),Mod[t]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare();
	for(int i=1;i<=n;i++){a[i]=read();tree.Add(i,a[i]);tree.Add(i+1,-a[i]);}
	while(m--){
		int op=read(),l=read(),r=read();
		if(op==1){int val=read();tree.Add(l,val);tree.Add(r+1,-val);}
		if(op==2){
			Mod[tot=0]=read();
			while(Mod[tot]!=1){tot++;Mod[tot]=phi[Mod[tot-1]];}
			printf("%d\n",Solve(l,r,0)%Mod[0]);
		}
	}
	return 0;
}
