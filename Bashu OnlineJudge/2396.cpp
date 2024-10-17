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
const ll P=1e9+7;
const ll N=1005;
const ll B=29;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,sum1,sum2,s1,s2;
ll a[N],b[N],sum[N];
map<ll,ll>Hash;
bool cmp(ll x,ll y){return x>y;}
ll DFS(ll x,ll y){
	ll ans=0,sta=0;
	if(x==n)return 1;
	if(sum[x]+3*(n-y+1)<a[x])return 0;
	if(y>n){
		for(ll i=x+1;i<=n;i++)b[i]=a[i]-sum[i];
		sort(b+x+1,b+n+1);
		for(ll i=x+1;i<=n;i++)sta=sta*B+b[i];
		if(Hash.find(sta)!=Hash.end())return Hash[sta];
		else return Hash[sta]=DFS(x+1,x+2);
	}
	if(s1&&sum[x]+3<=a[x]){
		sum[x]+=3;s1--;
		ans=(ans+DFS(x,y+1))%P;
		sum[x]-=3;s1++;
	}
	if(s1&&sum[y]+3<=a[y]){
		sum[y]+=3;s1--;
		ans=(ans+DFS(x,y+1))%P;
		sum[y]-=3;s1++;
	}
	if(s2&&sum[x]+1<=a[x]&&sum[y]+1<=a[y]){
		sum[x]++;sum[y]++;s2--;
		ans=(ans+DFS(x,y+1))%P;
		sum[x]--;sum[y]--;s2++;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	sum1=(n-1)*n/2;
	for(ll i=1;i<=n;i++){
		a[i]=read();
		sum2+=a[i];
	}
	s1=sum2-sum1*2;
	s2=sum1-s1;
	sort(a+1,a+n+1,cmp);
	printf("%lld",DFS(1,2));
	return 0;
}