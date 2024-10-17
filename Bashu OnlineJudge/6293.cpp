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
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
namespace Question1{
	const ll Mod=20021101;
	const ll N=1e7+5;
	bool vis[N];
	ll n,cnt,Ans;
	ll phi[N],prime[N];
	void Prepare(ll maxn){
		phi[1]=1;
		for(ll i=2;i<=maxn;i++){
			if(!vis[i]){prime[++cnt]=i;phi[i]=i-1;}
			for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
				vis[i*prime[j]]=1;
				if(i%prime[j])phi[i*prime[j]]=phi[i]*phi[prime[j]]%Mod;
				else {phi[i*prime[j]]=phi[i]*prime[j]%Mod;break;}
			}
		}
	}
	ll GetPhi(ll x){
		if(x<=1e7)return phi[x];
		ll Phi=x;
		for(ll i=2;i*i<=x;i++){
			if(x%i==0){
				Phi=Phi/i*(i-1);
				while(x%i==0)x/=i;
			}
		}
		if(x!=1)Phi=Phi/x*(x-1);
		return Phi;
	}
	void Main(){
		n=read();
		Prepare(1e7);
		for(ll i=1;i*i<=n;i++){
			if(n%i==0){
				ll x=i,y=n/i;
				if(x!=y)
				Ans=(Ans+GetPhi(x)*y%Mod)%Mod;
				Ans=(Ans+GetPhi(y)*x%Mod)%Mod;
			}
		}
		printf("%lld ",Ans);
	}
}
namespace Question2{
	const int N=3e5+5,M=1e7+5;
	int n,Ans,Lim,c0[M],c1[M],sum[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int c[]){
		x++;
		for(int i=x;i<=Lim+1;i+=lowbit(i))c[i]=(c[i]+1)&1;
	}
	int Ask(int x,int c[]){
		int ans=0;x++;
		for(int i=x;i>=1;i-=lowbit(i))ans=(ans+c[i])&1;
		return ans;
	}
	int Sum(int l,int r,int c[]){
		return Ask(r,c)-Ask(l-1,c);
	}
	void Main(){
		n=read();
		for(int i=1;i<=n;i++)sum[i]=sum[i-1]+read();
		for(int k=0;(1<<k)<=sum[n];k++){
			int ans=0;Lim=(1<<k)-1;
			for(int i=0;i<=n;i++){
				int lst=sum[i]&Lim;
				int type=(sum[i]>>k)&1;
				if(type){
					ans+=Sum(0,lst,c0);
					ans+=Sum(lst+1,Lim,c1);
					Add(lst,c1);
				}
				else{
					ans+=Sum(0,lst,c1);
					ans+=Sum(lst+1,Lim,c0);
					Add(lst,c0);
				}
				ans=ans&1;
			}
			Ans+=(1<<k)*(ans&1);
			for(int i=0;i<=Lim+1;i++)c0[i]=c1[i]=0;
		}
		printf("%d\n",Ans);
	}
}
int main(){
//	freopen("for.in","r",stdin);
//	freopen("for.out","w",stdout);
	Question1::Main();
	Question2::Main();
	return 0;
}