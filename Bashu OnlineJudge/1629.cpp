#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Min;
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
ll Multi(ll x,ll y,ll mod){
	ll ans=0,tot=x;
	while(y){
		if(y&1)ans=(ans+tot)%mod;
		tot=(tot+tot)%mod;
		y/=2;
	}
	return ans;
}
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=Multi(ans,tot,mod);
		tot=Multi(tot,tot,mod);
		y/=2;
	}
	return ans;
}
bool Miller_Rabin(ll n){
	if(n==2)return true;
	if(n<2||!(n&1))return false;
	int k=0,cnt=2;
	ll m=n-1;
	while(!(m&1)){
		k++;m>>=1;
	}
	for(int i=1;i<=cnt;i++){
		ll a=rand()%(n-1)+1;
		ll x=Pow(a,m,n),y=0;
		for(int j=1;j<=k;j++){
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
		Min=min(Min,n);
		return;
	}
	ll p=n;
	while(p>=n)p=Pollard_rho(p,k--);
	Find(p,k);Find(n/p,k);
}
ll n,num,ans,ansx,ansy,a[N];
void DFS(ll sum,ll depth){
	if(sum+n/sum<ans&&gcd(sum,n/sum)==1){
		ansx=sum;
		ansy=n/sum;
		ans=sum+n/sum;
	}
	if(sum*sum<n&&depth<=num){
		DFS(sum,depth+1);
		DFS(sum*a[depth],depth+1);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	srand(time(NULL));
	ll x,y;
	while(scanf("%lld%lld",&x,&y)!=EOF){
		num=0;
		n=y/x;
		while(n!=1){
			Min=n+1;
			Find(n,20031204);
			a[++num]=Min;
			n/=Min;
		}
		n=y/x;
		ans=x+y;
		DFS(1,1);
		ansx*=x;ansy*=x;
		if(ansx>ansy)swap(ansx,ansy);
		printf("%lld %lld\n",ansx,ansy);
	}
	return 0;
}