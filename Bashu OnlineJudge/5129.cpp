/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
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
const ll N=1e6+5;
const ll M=505;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline ll read(){
	ll s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
ll n,m,K,tot,Ans;
ll vis[N],sum[N];
ll a[M][M],c[M][M];
int main(){
//	freopen("rally.in","r",stdin);
//	freopen("rally.out","w",stdout);
	n=read();m=read();K=read();
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			a[i][j]=read()%K;
			c[i][j]=(c[i][j-1]+a[i][j])%K;
		}
	}
	for(ll i=1;i<=m;i++){
		for(ll j=i;j<=m;j++){
			ll Sum=0;
			vis[0]=++tot;sum[0]=1;
			for(ll k=1;k<=n;k++){
				Sum=(Sum+c[k][j]-c[k][i-1]+K)%K;
				if(vis[Sum]!=tot){
					vis[Sum]=tot;
					sum[Sum]=1;
				}
				else{
					Ans+=sum[Sum];
					sum[Sum]++;
				}
			}
		}
	}
	printf("%lld",Ans);
	return 0;
}