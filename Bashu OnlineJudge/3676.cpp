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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<ll,ll>Hash;
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y/=2;
	}
	return ans;
}
ll Inv(ll x,ll p){
	return Pow(x,p-2,p);
}
void Exgcd(ll a,ll b,ll &d,ll &x,ll &y){
	if(!b){
		d=a;x=1;y=0;
	}
	else{
		Exgcd(b,a%b,d,x,y);
		ll t=x;x=y;y=t-a/b*y;
	}
}
ll BSGS(ll a,ll b,ll p){
	if(a%p==0){
		if(b%p==0)return 1;
		else return -1;
	}
	a%=p;b%=p;
	Hash.clear();
	ll m=ceil(sqrt(p)),tmp=1;
	Hash[1]=m+1;
	//a^0=1,但是不能让Hash[1]=0,故用m+1表示 
	for(ll j=1;j<m;j++){
		tmp=tmp*a%p;
		if(!Hash[tmp])Hash[tmp]=j;
	}
	ll d=1;
	tmp=Pow(a,p-m-1,p);
	for(ll i=0;i<m;i++){
		ll j=Hash[b*d%p];
		if(j){
			if(j==m+1)j=0;
			return i*m+j;
		}
		d=d*tmp%p;
	}
	return -1;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		ll p=read(),a=read(),b=read(),X1=read(),t=read();
		if(X1==t){printf("1\n");continue;}
		if(a==0){
			if(b==t)printf("2\n");
			else printf("-1\n");
			continue;
		}
		if(a==1){
			ll T=((t+b-X1)%p+p)%p;
			ll gcd,x,y;//bx+py=T
			Exgcd(b,p,gcd,x,y);
			if(T%gcd)printf("-1\n");
			else{
				x*=(T/gcd);
				ll ans=(x%p+p)%p;
				if(ans)printf("%lld\n",ans);
				else printf("%lld\n",p);
			}
			continue;
		}
		b=b*Inv(1-a,p)%p;
		b=(t-b+p)*Inv((X1-b),p)%p;
		//a^x≡b(mod p)
		ll ans=BSGS(a,b,p);
		if(ans!=-1)ans++;
		printf("%lld\n",ans);
	}
	return 0;
}
/*
1
997 997 492 89 471
1
997 998 112 552 367
*/