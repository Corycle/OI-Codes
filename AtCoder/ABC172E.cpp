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
const int inf=0x3f3f3f3f;
const int N=5e5+5;
const int maxn=5e5;
const int mod=1e9+7;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int fac[N],inv[N],n,m,ans;
int A(int n,int m){return n<m?0:1ll*fac[n]*inv[n-m]%mod;}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read(),m=read();
	fac[0]=1;for(int i=1;i<=maxn;i++)fac[i]=1ll*fac[i-1]*i%mod;
	inv[1]=1;for(int i=2;i<=maxn;i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	inv[0]=1;for(int i=1;i<=maxn;i++)inv[i]=1ll*inv[i]*inv[i-1]%mod;
	for(int i=0;i<=n;i++)ans=(ans+1ll*(i&1?mod-1:1)*A(m,i)%mod*C(n,i)%mod*A(m-i,n-i)%mod*A(m-i,n-i)%mod)%mod;
	cout<<ans<<endl;
	return 0;
}
