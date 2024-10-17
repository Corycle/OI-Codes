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
const ll N=2000005;
const ll M=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
void FWT(ll a[],ll n,ll f){
	for(ll i=1;i<(1<<n);i<<=1){
		for(ll j=0;j<(1<<n);j++){
			if(i&j){
				ll x=a[j-i],y=a[j];
				a[j-i]=x+y;a[j]=x-y;
			}
		}
	}
	if(f==-1)for(ll i=0;i<(1<<n);i++)a[i]/=(1<<n);
}
char s[M];
ll n,m,a[25][M],A[N],B[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		scanf("%s",s+1);
		for(ll j=1;j<=m;j++)a[i][j]=s[j]-'0';
	}
	for(ll j=1;j<=m;j++){
		ll num=0;
		for(ll i=1;i<=n;i++)num=num*2+a[i][j];
		A[num]++;
	}
	for(ll i=0;i<(1<<n);i++)B[i]=B[i>>1]+(i&1);
	for(ll i=0;i<(1<<n);i++)B[i]=min(B[i],n-B[i]);
	FWT(A,n,1);FWT(B,n,1);
	for(ll i=0;i<(1<<n);i++)A[i]=A[i]*B[i];
	FWT(A,n,-1);
	ll ans=n*m;
	for(ll i=0;i<(1<<n);i++){
		ans=min(ans,A[i]);
	}
	printf("%lld",ans);
	return 0;
}