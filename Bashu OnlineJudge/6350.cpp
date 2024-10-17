/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=998244353;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,K,Pos,Ans;
ll a[N],Fac[N],Inv[N],sum[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(){
	ll maxn=1e5;
	Fac[0]=Fac[1]=Inv[0]=Inv[1]=1;
	for(ll i=2;i<=maxn;i++)Fac[i]=Fac[i-1]*i%Mod;
	for(ll i=2;i<=maxn;i++)Inv[i]=Inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(ll i=2;i<=maxn;i++)Inv[i]=Inv[i-1]*Inv[i]%Mod;
}
ll Sum(ll l,ll r){return sum[r]-sum[l-1];}
ll P(ll n,ll m){return n<m?0:Fac[n]*Inv[n-m]%Mod;}
ll C(ll n,ll m){return n<m?0:Fac[n]*Inv[n-m]%Mod*Inv[m]%Mod;}
ll G(ll len1,ll len2){//1在len1所属转移点最后一个前,有len1种选择,len2所属转移点为最后一个 
	if(len1+len2+1>m)return 0;
	return C(m,len1+len2+1)*C(len1+len2,len1+1)%Mod*len1%Mod*P(n-len1-len2-1,m-len1-len2-1)%Mod;
}
ll H(ll len1,ll len2){//1在len1所属转移点最后一个后,有1种选择,len2所属转移点为最后一个 
	if(len1+len2+1>m)return 0;
	return C(m,len1+len2+1)*C(len1+len2,len1+1)%Mod*P(n-len1-len2-1,m-len1-len2-1)%Mod;
}
ll F(ll len1,ll len2){//左边至少为len1,右边至少为len2,不选1 
	if(len1+len2>m)return 0;
	return C(m,len1+len2)*C(len1+len2,len1)%Mod*P(n-1-len1-len2,m-len1-len2)%Mod;
}
ll S(ll len){//左边或右边至少选len,1不是最后选,2或n不能选 
	if(len+1>m)return 0;
	return C(m,len+1)*len%Mod*P(n-1-len-1,m-len-1)%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();Prepare();
	while(T--){
		Ans=0;Pos=1;
		n=read();m=read();K=read();
		for(ll i=1;i<=n;i++)a[i]=read();
		if(K==0){printf("1\n");continue;}
		for(ll i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
		//不选1 
		for(ll r=1;r<=m+1;r++){
			if(sum[r]>=K){
				Pos=r;
				Ans+=F(0,r-1)-F(1,r-1);
				break;
			}
		}
		for(ll l=n;n-l+1<=m;l--){//左边恰好为l
			ll len1=n-l+1,len2=Pos-1;// 2 n ; n 2 ; n
			while(len1+len2>m||Pos>1&&Sum(l,n)+Sum(1,Pos-1)>=K){Pos--;len2--;}
			if(Sum(l,n)+Sum(1,Pos)>=K)Ans+=F(len1,len2)-F(len1+1,len2);
		}
		Ans=(Ans%Mod+Mod)%Mod;
		//选1 
		if(m>=2){
			for(ll r=2;r<=m;r++)if(Sum(1,r)>=K){Ans+=S(r-1);break;}//1 2
			for(ll l=n;n-l+1<=m;l--)if(Sum(l,n)+a[1]>=K){Ans+=S(n-l+1);break;}//1 n
			Ans=(Ans%Mod+Mod)%Mod;
		}
		if(m>=3){
			// 2 n 1 = 0
			// n 2 1 = 0
			Pos=m-1;//1 2 n ; 1 n 2
			for(ll l=n;n-l+1<m-1;l--){
				ll len1=n-l+1,len2=Pos-1;
				while(len1+len2+1>m||Pos-1>1&&Sum(l,n)+Sum(2,Pos-1)+a[1]*2>=K)Pos--,len2--;
				if(len1&&len2&&Sum(l,n)+Sum(2,Pos)+a[1]*2>=K){
					Ans+=G(len1,len2)-G(len1+1,len2);
					Ans+=G(len2,len1)-G(len2,len1+1);
				}
			}
			Pos=m-1;//2 1 n ; n 1 2
			for(ll l=n;n-l+1<m-1;l--){
				ll len1=n-l+1,len2=Pos-1;
				while(len1+len2+1>m||Pos-1>1&&Sum(l,n)+Sum(1,Pos-1)>=K)Pos--,len2--;
				if(len1&&len2&&Sum(l,n)+Sum(1,Pos)>=K){
					Ans+=H(len1,len2)-H(len1+1,len2);
					Ans+=H(len2,len1)-H(len2,len1+1);
				}				
			}
			Ans=(Ans%Mod+Mod)%Mod;
		}
		printf("%lld\n",Ans*Pow(P(n,m),Mod-2)%Mod);
	}
	return 0;
}