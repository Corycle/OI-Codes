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
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,sum,num1,num2,fa[N];
struct edge{ll s,t,w;}e[N];
bool cmp(edge A,edge B){return A.w<B.w;}
ll Find(ll x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Check(ll C){
	ll l=1,r=m;
	sum=num1=num2=0;
	for(ll i=1;i<=n;i++)fa[i]=i;
	while(num1+num2!=(n-1)/2*2){
		if(C-e[l].w>=e[r].w){
			ll x=e[l].s,y=e[l].t;
			if(Find(x)==Find(y)){l++;continue;}
			fa[Find(x)]=fa[Find(y)];
			sum+=C-e[l].w;num1++;l++;
		}
		else{
			ll x=e[r].s,y=e[r].t;
			if(Find(x)==Find(y)){r--;continue;}
			fa[Find(x)]=fa[Find(y)];
			sum+=e[r].w;num2++;r--;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		e[i].w=read();
	}
	sort(e+1,e+m+1,cmp);
	ll l=0,r=2e9,ans=0;
	while(l<=r){
		ll mid=(l+r)>>1;Check(mid);
		if(num1==(n-1)/2){ans=mid;break;}
		if(num1>=(n-1)/2){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	Check(ans);
	printf("%lld",sum-ans*((n-1)/2));
	return 0;
}