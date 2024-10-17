#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=300005;
const ll M=20;
const ll g=3;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll R[N];
ll Multi(ll x,ll y,ll mod){
	ll ans=0,tot=x;
	while(y){
		if(y&1)ans=(ans+tot)%mod;
		tot=(tot+tot)%mod;
		y>>=1;
	}
	return ans;
}
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y>>=1;
	}
	return ans;
}
struct Number_Theoretic_Transforms{
	ll A[N],Mod;
	void NTT(ll a[],ll n,ll f){
		for(ll i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
		for(ll i=1;i<n;i<<=1){
			ll Wn=Pow(g,Mod-1+f*(Mod-1)/(i<<1),Mod);
			for(ll j=0;j<n;j+=(i<<1)){
				ll W=1;
				for(ll k=0;k<i;k++){
					ll x=a[j+k],y=W*a[j+k+i]%Mod;
					a[j+k]=(x+y)%Mod;a[j+k+i]=(x-y+Mod)%Mod;
					W=(W*Wn)%Mod;
				}
			}
		}
		if(f==-1){
			ll inv=Pow(n,Mod-2,Mod);
			for(ll i=0;i<n;i++)a[i]=(a[i]*inv)%Mod;
		}
	}
}ntt[2];
ll p=100003;
ll n,m,maxn,Inv0,Inv1;
ll a[N],Ans[N],F[M][N];
ll P[2]={469762049,998244353};
void Solve(ll l,ll r,ll x){
	if(l==r){
		F[x][0]=1;
		F[x][1]=a[l]%p;
		return;
	}
	ll len=1,L=0;
	ll mid=(l+r)>>1;
	ll l1=mid-l+1,l2=r-mid;
	while(len<=r-l+1){len<<=1;L++;}
	
	Solve(l,mid,x+1);//DFS Left
	for(ll i=0;i<=l1;i++)F[x][i]=F[x+1][i];
	for(ll i=l1+1;i<len;i++)F[x][i]=F[x+1][i]=0;
	
	Solve(mid+1,r,x+1);//DFS Right
	for(ll i=0;i<=l2;i++)ntt[0].A[i]=ntt[1].A[i]=F[x+1][i];
	for(ll i=l2+1;i<len;i++)ntt[0].A[i]=ntt[1].A[i]=0;
	
	for(ll i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	
	ntt[0].NTT(F[x],len,1);//NTT Left
	ntt[0].NTT(ntt[0].A,len,1);
	for(ll i=0;i<len;i++)ntt[0].A[i]=ntt[0].A[i]*F[x][i]%P[0];
	ntt[0].NTT(ntt[0].A,len,-1);
	ntt[0].NTT(F[x],len,-1);
	
	ntt[1].NTT(F[x],len,1);//NTT Right
	ntt[1].NTT(ntt[1].A,len,1);
	for(ll i=0;i<len;i++)ntt[1].A[i]=ntt[1].A[i]*F[x][i]%P[1];
	ntt[1].NTT(ntt[1].A,len,-1);
	ntt[1].NTT(F[x],len,-1);
	
	ll M=P[0]*P[1];//Merge Left and Right
	for(ll i=0;i<len;i++){
		ll a=ntt[0].A[i],b=ntt[1].A[i];
		F[x][i]=(Multi(a*P[1]%M,Inv0,M)+Multi(b*P[0]%M,Inv1,M))%M%p;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	ntt[0].Mod=P[0];
	ntt[1].Mod=P[1];
	Inv0=Pow(P[1],P[0]-2,P[0]);
	Inv1=Pow(P[0],P[1]-2,P[1]);
	for(ll i=1;i<=n;i++)a[i]=read();
	Solve(1,n,0);
	while(m--)printf("%lld\n",F[0][read()]%p);
	return 0;
}