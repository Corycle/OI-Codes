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
const int Mod=998244353;
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,fac[N],inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(int maxn){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=maxn;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
int Pow(int x,int y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare(max(n,m));
	for(int i=0;i<=min(n,m);i++){
		Ans=mod(Ans+1ll*(i&1?Mod-1:1)*C(n,i)%Mod*C(m,i)%Mod*fac[i]%Mod*Pow(m+1,n-i)%Mod*Pow(n+1,m-i)%Mod);
	}
	printf("%d",Ans);
	return 0;
}
