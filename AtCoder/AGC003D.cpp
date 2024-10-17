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
#define fst first
#define scd second
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[N];
map<ll,ll>Rev,Num;
int n,m,Ans,cnt,vis[N],prime[N];
void Prepare(int maxn){
	for(int i=2;i<=maxn;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=(int)(ceil(pow(1e10,1/3.0)));Prepare(m);
	for(int i=1;i<=n;i++){
		a[i]=read();
		ll tmp=a[i],rev=1;
		for(int j=1;j<=cnt;j++){
			if(a[i]%prime[j])continue;
			ll p2=1ll*prime[j]*prime[j];
			ll p3=1ll*prime[j]*prime[j]*prime[j];
			while(tmp%prime[j]==0)tmp/=prime[j];
			while(a[i]%p3==0)a[i]/=p3;
			if(a[i]%p2==0)rev*=prime[j];
			else if(a[i]%prime[j]==0)rev*=p2;
		}
		if(tmp>1e5){
			ll x=(ll)(round(sqrt(tmp)));
			if(x*x==tmp)rev*=x;else rev=-1;
		}
		else if(tmp!=1)rev*=tmp*tmp;
		Rev[a[i]]=rev;Num[a[i]]++;
	}
	for(auto tmp:Num){
		if(!Num.count(Rev[tmp.fst]))Ans+=tmp.scd;
		else if(tmp.fst<Rev[tmp.fst])Ans+=max(tmp.scd,Num[Rev[tmp.fst]]);
	}
	printf("%lld\n",Ans+Num.count(1));
	return 0;
}
