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
const ll N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N][N];
ll n,m,tot,Ans,a[N],b[N],f[N],fac[N];
ll Gauss(ll n){
	ll ans=0;
	for(ll i=1;i<=m;i++){
		ll t=0;
		for(ll j=ans+1;j<=n;j++)if((a[j]>>i)&1)t=j;
		if(!t)continue;ans++;swap(a[ans],a[t]);
		for(ll j=1;j<=n;j++){
			if(j==ans||!((a[j]>>i)&1))continue;
			a[j]^=a[ans];
		}
	}
//	cout<<"Gauss: "<<ans<<endl;
	return ans;
}
void Calc(){
	ll cnt=0,t=0;
	for(ll i=1;i<=n;i++){
		for(ll j=i+1;j<=n;j++){
			t++;
			if(b[i]!=b[j])a[++cnt]=f[t];
		}
	}
	Ans+=(1ll<<(m-Gauss(cnt)))*fac[tot-1]*(tot&1?1:-1);
//	for(ll i=1;i<=n;i++)cout<<b[i]<<" ";cout<<endl;
//	cout<<Ans<<" "<<tot<<" "<<fac[tot-1]<<endl;
}
void DFS(ll x){
	if(x==n+1){Calc();return;}
	if(tot){
		for(ll i=1;i<=tot;i++){b[x]=i;DFS(x+1);}
	}
	b[x]=++tot;DFS(x+1);tot--;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();
	for(ll i=1;i<=m;i++)scanf("%s",s[i]+1);
	ll len=strlen(s[1]+1);
	for(ll i=1;i<=10;i++)if(len==i*(i-1)/2)n=i;
	fac[0]=1;
	for(ll i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i;
	for(ll i=1;i<=len;i++){
		for(ll j=1;j<=m;j++){
			if(s[j][i]=='1')f[i]|=(1ll<<j);
		}
	}
	DFS(1);
	printf("%lld",Ans);
	return 0;
}