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
const ll M=1<<16;
const ll N=3005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,cnt,tot;
vector<ll>V[N];
ll f[M],g[M],p[N];
ll num[N],vis[N],prime[N];
void Prepare(ll maxn){
	for(ll i=2;i<=maxn;i++){
		if(!vis[i])prime[++cnt]=i;
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;i++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll n=read();Prepare(n);
	for(ll i=1;i<=n;i++){
		ll x=i;
		for(ll j=1;j<=cnt;j++){
			while(x%prime[j]==0){
				num[prime[j]]^=1;
				x/=prime[j];
			}
		}
	}
	ll tot=0;
	for(ll i=1;i<=cnt&&prime[i]*prime[i]<=n;i++){//小于等于sqrt(n)的素数 
		if(num[prime[i]])p[++tot]=prime[i];
	}
	for(ll i=1;i<=n;i++){
		ll flag=1,Sta=0,x=i;
		for(ll j=1;j<=tot;j++){
			if(x%p[j]==0){
				x/=p[j];Sta|=(1<<(j-1));
				if(x%p[j]==0){flag=0;break;}
			}
		}//将可删的数加入vector 
		if(flag&&(x==1||(!vis[x]&&num[x])))V[x].push_back(Sta);
	}
	f[0]=1;
	for(ll i=0;i<V[1].size();i++){
		memcpy(g,f,sizeof(g));
		for(ll S=0;S<(1<<tot);S++){
			if((V[1][i]&S)==V[1][i]){
				g[S]+=f[S^V[1][i]];
			}
		}
		memcpy(f,g,sizeof(f));
	}
	for(ll k=2;k<=n;k++){
		if(!V[k].size())continue;
		memset(g,0,sizeof(g));
		for(ll i=0;i<V[k].size();i++){
			for(ll S=0;S<(1<<tot);S++){
				if((V[k][i]&S)==V[k][i]){
					g[S]+=f[S^V[k][i]];
				}
			}
		}
		memcpy(f,g,sizeof(f));
	}
	printf("%lld",f[(1<<tot)-1]);
	return 0;
}