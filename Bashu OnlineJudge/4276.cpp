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
#define ld long double
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=1e9+7;
const int N=3005;
inline ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll q[N];
inline int mod(int x){return x>=Mod?x-Mod:x;}
inline ll gcd(ll x,ll y){return y==0?x:gcd(y,x%y);}
inline ll Multi(ll x,ll y,ll mod){
	return (x*y-(ll)(((ld)x*y+0.5)/(ld)mod)*mod+mod)%mod;
}
inline ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=Multi(ans,tot,mod);
		tot=Multi(tot,tot,mod);
		y>>=1;
	}
	return ans;
}
inline ll Pow(ll x,ll y){
	ll ans=1,tot=x%Mod;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
bool Miller_Rabin(ll n){
	if(n==2)return true;
	if(n<2||!(n&1))return false;
	ll m=n-1,k=0,cnt=5;
	while(!(m&1)){k++;m>>=1;}
	for(ll i=1;i<=cnt;i++){
		ll a=rand()%(n-1)+1;
		ll x=Pow(a,m,n),y=0;
		for(ll j=1;j<=k;j++){
			y=Multi(x,x,n);
			if(y==1&&x!=1&&x!=n-1)return false;
			x=y;
		}
		if(y!=1)return false;
	}
	return true;
}
ll Pollard_rho(ll n,ll c){
	ll x=rand()%(n-1)+1;
	ll y=x,i=1,k=2;
	while(1){
		i++;
		x=(Multi(x,x,n)+c)%n;
		ll d=gcd((y-x+n)%n,n);
		if(1<d&&d<n)return d;
		if(x==y)return n;
		if(i==k){y=x;k<<=1;}
	}
}
void Find(ll n,ll k){
	if(n==1)return;
	if(Miller_Rabin(n)){
		q[++q[0]]=n;
		return;
	}
	ll p=n;
	while(p>=n)p=Pollard_rho(p,k--);
	Find(p,k);Find(n/p,k);
}
ll p[N],num[N],t[N],B[N],C[N][N];
void Prepare(){
	C[0][0]=1;
	for(int i=1;i<=3002;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);
		}
	}
	B[0]=1;
	for(int i=1;i<3002;i++){
		for(int j=0;j<i;j++){
			B[i]=mod(B[i]+C[i+1][j]*B[j]%Mod);
		}
		B[i]=B[i]*Pow(Mod-C[i+1][i],Mod-2)%Mod;
	}
	B[1]=(Mod-B[1])%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare();
	int T=read();
	srand(time(NULL));
	while(T--){
		q[0]=p[0]=num[0]=0;
		ll n=read(),x=read(),y=read();
		Find(n,100007);
		sort(q+1,q+q[0]+1);
		for(int i=1;i<=q[0];i++){
			if(i==1||q[i]!=q[i-1]){
				p[++p[0]]=q[i];
				num[++num[0]]=1;
			}
			else num[num[0]]++;
		}
		ll inv=Pow(y+1,Mod-2);
		for(int i=0;i<=y;i++){
			t[i]=C[y+1][i]*B[i]%Mod*inv%Mod;
		}
		ll ans=0;
		for(int k=0;k<=y;k++){
			ll dlt=1;
			for(int i=1;i<=p[0];i++){
				ll tmp=0,d=1,pi=p[i];
				ll pk=Pow(pi,num[i]);
				ll Inv=Pow(pi,Mod-2);
				ll Inv_d=1,P=Pow(pi,y);
				for(int j=0;j<=num[i];j++){
					ll t1=Pow(pk*Inv_d%Mod,y-k+1);
					ll t2=Pow(pk*Inv_d%Mod*Inv%Mod,y-k+1)*P%Mod;
					if(j==num[i])tmp=mod(tmp+Pow(d,x)*t1%Mod);
					else tmp=mod(tmp+Pow(d,x)*(t1-t2+Mod)%Mod);
					d=d*pi%Mod;Inv_d=Inv_d*Inv%Mod;
				}
				dlt=(dlt*tmp%Mod*Pow(pk,y)%Mod)%Mod;
			}
			ans=mod(ans+dlt*t[k]%Mod);
		}
		printf("%lld\n",ans);
	}
	return 0;
}