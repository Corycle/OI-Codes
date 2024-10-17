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
const ll inf=0x3f3f3f3f;
const ll p=1000000007;
const ll N=1000005;
int read(){
    int s=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
    return s*f;
}
ll Pow(ll x,ll y,ll mod){
    ll ans=1,tot=x;
    while(y){
        if(y&1)ans=(ans*tot)%mod;
        tot=(tot*tot)%mod;
        y>>=1;
    }
    return ans;
}
ll Inv(ll x,ll mod){
    return Pow(x,mod-2,mod);
}
ll n,k;
ll a[N],f[N],g[N];
ll Lagrange(){
    f[0]=g[0]=1;
    ll ans=0,tmp=1;
    for(ll i=1;i<=k+2;i++){
        tmp=tmp*(n-i)%p;
        f[i]=f[i-1]*i%p;
        g[i]=-g[i-1]*i%p;
    }
    for(ll i=1;i<=k+2;i++){
        ans=(ans+a[i]*tmp%p*Inv(n-i,p)%p*Inv(f[i-1]*g[k+2-i]%p,p)%p)%p;
    }
    return (ans+p)%p;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
    n=read();k=read();
    for(ll i=1;i<=k+2&&i<=n;i++){
        a[i]=(a[i-1]+Pow(i,k,p))%p;
    }
    if(n<=k+2)printf("%lld",a[n]);
    else printf("%lld",Lagrange());
    return 0;
}
