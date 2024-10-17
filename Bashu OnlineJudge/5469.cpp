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
const int N=10100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,A,B,p,q,f[N];
int Fac[N],Inv[N],PowA[N],PowB[N],InvA[N],InvB[N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int C(int n,int m){
	return n<m?0:1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;
}
void Prepare(int maxn){
	Fac[0]=Fac[1]=Inv[0]=Inv[1]=1;
	for(int i=2;i<=maxn;i++)Fac[i]=1ll*Fac[i-1]*i%Mod;
	for(int i=2;i<=maxn;i++)Inv[i]=1ll*Inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=maxn;i++)Inv[i]=1ll*Inv[i-1]*Inv[i]%Mod;
	PowA[0]=PowB[0]=InvA[0]=InvB[0]=1;
	int inva=Pow(A,Mod-2),invb=Pow(B,Mod-2);
	for(int i=1;i<=maxn;i++){
		PowA[i]=1ll*PowA[i-1]*A%Mod;
		PowB[i]=1ll*PowB[i-1]*B%Mod;
		InvA[i]=1ll*InvA[i-1]*inva%Mod;
		InvB[i]=1ll*InvB[i-1]*invb%Mod;
	}
}
int Ask1(int x,int y){
	int ans=0,dep=p-x;
	for(int i=1;i<=y;i++){
		int f1=dep,f2=y-i,t=(f2&1?Mod-1:1);
		ans=(ans+1ll*InvA[f1+f2]*PowB[f2]%Mod*C(f1+f2-1,f1-1)%Mod*f[i]%Mod*t%Mod)%Mod;
	}
	return ans;
}
int Ask2(int x,int y){
	int ans=0,dep=x-p;
	for(int i=max(y-dep,1);i<=y;i++){
		int f2=y-i,f1=dep-f2;
		ans=(ans+1ll*PowA[f1]*PowB[f2]%Mod*C(f1+f2,f1)%Mod*f[i]%Mod)%Mod;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();n=read();A=read(),B=read();p=read();q=read();
	for(int i=1;i<=n;i++)f[i]=read();
	Prepare(n+m);
	while(q--){
		int x=read(),y=read();
		if(x==p)printf("%d\n",f[y]);
		if(x<p)printf("%d\n",Ask1(x,y));
		if(x>p)printf("%d\n",Ask2(x,y));
	}
	return 0;
}