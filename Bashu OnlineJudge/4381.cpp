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
const double Pi=acos(-1);
const ll Mod=1e9+7;
const ll N=600005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll R[N];
void FFT(complex<double>a[],ll n,ll f){
	for(ll i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(ll i=1;i<n;i<<=1){
		complex<double>Wn(cos(Pi/i),f*sin(Pi/i));
		for(ll j=0;j<n;j+=(i<<1)){
			complex<double>W(1,0);
			for(ll k=0;k<i;k++){
				complex<double>x=a[j+k],y=W*a[j+k+i];
				a[j+k]=x+y;a[j+k+i]=x-y;W*=Wn;
			}
		}
	}
	if(f==-1)for(ll i=0;i<n;i++)a[i]/=n;
}
char s[N],S[N];
ll n,m,p[N],fac[N];
complex<double>a[N],b[N],c[N];
ll Manacher(){
	S[0]='@';S[++m]='#';
	for(ll i=1;i<=n;i++){
		S[++m]=s[i];
		S[++m]='#';
	}
	ll maxx=0,k=0,ans=0;
	for(ll i=1;i<=m;i++){
		if(maxx>i)p[i]=min(p[k*2-i],maxx-i);
		else p[i]=1;
		while(S[i+p[i]]==S[i-p[i]])p[i]++;
		if(p[i]+i>maxx){maxx=p[i]+i;k=i;}
		ans=(ans+p[i]/2)%Mod;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	for(ll i=1;i<=n;i++){
		if(s[i]=='a')a[i]=1;
		if(s[i]=='b')b[i]=1;
	}
	ll len=1,L=0;
	while(len<n+n){len<<=1;L++;}
	for(ll i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	FFT(a,len,1);FFT(b,len,1);
	for(ll i=0;i<len;i++)c[i]=a[i]*a[i]+b[i]*b[i];
	FFT(c,len,-1);
	ll ans=0;fac[0]=1;
	for(ll i=1;i<N;i++)fac[i]=(fac[i-1]*2)%Mod;
	for(ll i=0;i<len;i++){
		ll tmp=(ll)(c[i].real()+0.5);
		ans=(ans+fac[(tmp+1)>>1]-1)%Mod;
	}
	printf("%lld",(ans+Mod-Manacher())%Mod);
	return 0;
}