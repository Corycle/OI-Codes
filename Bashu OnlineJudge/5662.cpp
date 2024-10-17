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
const int N=1e5+5;
const int M=30;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,a[N],Mod[M];
ll Pow(ll x,ll y,ll mod){
	ll ans=1;
	while(y){
		if(y&1){ans=ans*x;if(ans>=mod)ans=ans%mod+mod;}
		x=x*x;if(x>=mod)x=x%mod+mod;y>>=1;
	}
	return ans;
}
int Phi(int x){
	int phi=x;
	for(int i=2;1ll*i*i<=x;i++)if(x%i==0){phi=phi/i*(i-1);while(x%i==0)x/=i;}
	if(x!=1)phi=phi/x*(x-1);
	return phi;
}
int Solve(int l,int r,int t){
	if(l==r||t==tot)return a[l]<Mod[t]?a[l]:a[l]%Mod[t]+Mod[t];
	return Pow(a[l],Solve(l+1,r,t+1),Mod[t]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Mod[0]=m;
	while(Mod[tot]!=1){tot++;Mod[tot]=Phi(Mod[tot-1]);}
	for(int i=1;i<=n;i++)a[i]=read();
	int Q=read();
	while(Q--){
		int l=read(),r=read();
		printf("%d\n",Solve(l,r,0)%m);
	}
	return 0;
}