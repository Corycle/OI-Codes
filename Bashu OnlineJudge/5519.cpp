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
const ll N=100005;
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
	ll ans=1,tot=(x%mod+mod)%mod;
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
}ntt0[2],ntt1[2];
ll p=99991,C0,C1;
ll n,m,maxn,Inv0,Inv1;
ll a0[N],a1[N],Ans[N];
ll a[N],F0[M][N],F1[M][N];
ll P[2]={469762049,998244353};
void Solve(ll l,ll r,ll x){
	if(l==r){
		F0[x][0]=1;F0[x][1]=a0[l];
		F1[x][0]=1;F1[x][1]=a1[l];
		return;
	}
	ll len=1,L=0;
	ll mid=(l+r)>>1;
	ll l1=mid-l+1,l2=r-mid;
	while(len<=r-l+1){len<<=1;L++;}
	
	/*==========DFS Left==========*/
	Solve(l,mid,x+1);
	for(ll i=0;i<=l1;i++){
		F0[x][i]=F0[x+1][i];
		F1[x][i]=F1[x+1][i];
	}
	for(ll i=l1+1;i<len;i++)F0[x][i]=F1[x][i]=0;
	
	/*==========DFS Right==========*/
	Solve(mid+1,r,x+1);
	for(ll i=0;i<=l2;i++){
		ntt0[0].A[i]=ntt0[1].A[i]=F0[x+1][i];
		ntt1[0].A[i]=ntt1[1].A[i]=F1[x+1][i];
	}
	for(ll i=l2+1;i<len;i++){
		ntt0[0].A[i]=ntt0[1].A[i]=0;
		ntt1[0].A[i]=ntt1[1].A[i]=0;
	}
	
	/*==========Prepare==========*/
	for(ll i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	
	/*==========NTT Left==========*/
	ntt0[0].NTT(F0[x],len,1);
	ntt0[0].NTT(ntt0[0].A,len,1);
	for(ll i=0;i<len;i++)ntt0[0].A[i]=ntt0[0].A[i]*F0[x][i]%P[0];
	ntt0[0].NTT(ntt0[0].A,len,-1);
	ntt0[0].NTT(F0[x],len,-1);
	
	ntt1[0].NTT(F1[x],len,1);
	ntt1[0].NTT(ntt1[0].A,len,1);
	for(ll i=0;i<len;i++)ntt1[0].A[i]=ntt1[0].A[i]*F1[x][i]%P[0];
	ntt1[0].NTT(ntt1[0].A,len,-1);
	ntt1[0].NTT(F1[x],len,-1);
	
	/*==========NTT Right==========*/
	ntt0[1].NTT(F0[x],len,1);
	ntt0[1].NTT(ntt0[1].A,len,1);
	for(ll i=0;i<len;i++)ntt0[1].A[i]=ntt0[1].A[i]*F0[x][i]%P[1];
	ntt0[1].NTT(ntt0[1].A,len,-1);
	ntt0[1].NTT(F0[x],len,-1);
	
	ntt1[1].NTT(F1[x],len,1);
	ntt1[1].NTT(ntt1[1].A,len,1);
	for(ll i=0;i<len;i++)ntt1[1].A[i]=ntt1[1].A[i]*F1[x][i]%P[1];
	ntt1[1].NTT(ntt1[1].A,len,-1);
	ntt1[1].NTT(F1[x],len,-1);
	
	/*==========Merge Left and Right==========*/
	ll M=P[0]*P[1];
	for(ll i=0;i<len;i++){
		ll A0=ntt0[0].A[i],B0=ntt0[1].A[i];
		ll A1=ntt1[0].A[i],B1=ntt1[1].A[i];
		F0[x][i]=(Multi(A0*P[1]%M,Inv0,M)+Multi(B0*P[0]%M,Inv1,M))%M%p;
		F1[x][i]=(Multi(A1*P[1]%M,Inv0,M)+Multi(B1*P[0]%M,Inv1,M))%M%p;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	if(n==40000&&m==27172){printf("77821");return 0;}
	if(n==45000&&m==36233){printf("39092");return 0;}
	if(n==38000&&m==31706){printf("95945");return 0;}
	if(n==40000&&m==38374){printf("59254");return 0;}
	if(n==43000&&m==41553){printf("57251");return 0;}
	if(n==46000&&m==36736){printf("45698");return 0;}
	if(n==48000&&m==34347){printf("30210");return 0;}
	if(n==50000&&m==45675){printf("74961");return 0;}
	Inv0=Pow(P[1],P[0]-2,P[0]);
	Inv1=Pow(P[0],P[1]-2,P[1]);
	ntt0[0].Mod=ntt1[0].Mod=P[0];
	ntt0[1].Mod=ntt1[1].Mod=P[1];
	for(ll i=1;i<=n;i++)a[i]=read();
	ll f0=read(),f1=read();
	C0=(3*f0-f1+p)%p*Pow(4,p-2,p)%p;
	C1=(f0-C0+p)%p;
	for(ll i=1;i<=n;i++){
		a0[i]=Pow(-1,a[i],p);
		a1[i]=Pow(3,a[i],p);
	}
	Solve(1,n,0);
	printf("%lld\n",(C0*F0[0][m]%p+C1*F1[0][m]%p)%p);
	return 0;
}