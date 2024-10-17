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
const int N=10000005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int Maxn=2;
int inv[N],Fac[N],Inv[N];
void Prepare(int maxn){
	if(Maxn<maxn){
		for(int i=Maxn;i<=maxn;i++){
			Fac[i]=1ll*Fac[i-1]*i%Mod;
			inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
			Inv[i]=1ll*Inv[i-1]*inv[i]%Mod;
		}
		Maxn=maxn;
	}
}
int Sqr(int x){return 1ll*x*x%Mod;}
int C(int n,int m){
	return 1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;
}
int main(){
//	freopen("ball.in","r",stdin);
//	freopen("ball.out","w",stdout);
	Fac[0]=Fac[1]=1;
	Inv[0]=Inv[1]=1;
	inv[0]=inv[1]=1;
	int T=read();
	while(T--){
		int n=read(),m=read();Prepare(n);
		printf("%lld\n",1ll*Sqr(C(n,m))*Fac[m]%Mod);
	}
	return 0;
}