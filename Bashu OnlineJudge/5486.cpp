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
map<ll,ll>Hash;
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
void Exgcd(ll a,ll b,ll &d,ll &x,ll &y){
	if(b==0){d=a;x=1;y=0;}
	else{
		Exgcd(b,a%b,d,x,y);
		ll t=x;x=y;y=t-a/b*y;
	}
}
ll EXBSGS(ll a,ll b,ll p){
	if(b==1)return 0;
	ll t=1,cnt=0,tmp=gcd(a,p);
	while(tmp!=1){
		if(b%tmp)return -1;
		b/=tmp;p/=tmp;t*=a/tmp;cnt++;
		if(b==t)return cnt;
		tmp=gcd(a,p);
	}
	Hash.clear();
	ll m=ceil(sqrt(p));
	Hash[1]=m+1;tmp=1;
	for(ll i=1;i<m;i++){
		tmp=tmp*a%p;
		if(!Hash[tmp])Hash[tmp]=i;
	}
	tmp=tmp*a%p;
	ll gcd=0,x=0,y=0,d=1;
	Exgcd(t,p,gcd,x,y);
	x=(x%(p/gcd)+(p/gcd))%(p/gcd);
	b=b*x%p;
	for(int i=0;i<=m;i++){
		Exgcd(d,p,gcd,x,y);
		x=(x*(b/gcd)%(p/gcd)+(p/gcd))%(p/gcd);
		if(Hash[x]){
			if(Hash[x]==m+1)return i*m+cnt;
			return i*m+cnt+Hash[x];
		}
		d=d*tmp%p;
	}
	return -1;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll k=0,p=0,n=0;
	while(scanf("%lld%lld%lld",&k,&p,&n)!=EOF){
		if(n>=p)printf("-1\n");
		else{
			k%=p;n%=p;
			printf("%lld\n",EXBSGS(k,n,p));
		}
	}
	return 0;
}