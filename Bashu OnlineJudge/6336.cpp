/*====Corycle====*/
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
const int inf=0x3f3f3f3f;
const int Mod=1e9+7;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,f[N],q[N],Fac[N],Inv[N],inv[N];
int C(int n,int m){
	if(n<m)return 0;
	return 1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int x=0;
	while(scanf("%d",&x)!=EOF){
		q[++m]=x;n=max(n,x);
	}
	n*=2;
	Fac[0]=Inv[0]=inv[0]=1;
	Fac[1]=Inv[1]=inv[1]=1;
	for(int i=2;i<=n;i++)Fac[i]=1ll*Fac[i-1]*i%Mod;
	for(int i=2;i<=n;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=n;i++)Inv[i]=1ll*Inv[i-1]*inv[i]%Mod;
	for(int j=1;j<=m;j++){
		n=q[j];
		if(n<=2)printf("0\n");
		else{
			int Ans=0;
			for(int i=0;i<=n;i++){
				if(i%2==0)Ans=(Ans+1ll*2*n%Mod*inv[2*n-i]%Mod*Fac[n-i]%Mod*C(n*2-i,i)%Mod+Mod)%Mod;
				if(i%2==1)Ans=(Ans-1ll*2*n%Mod*inv[2*n-i]%Mod*Fac[n-i]%Mod*C(n*2-i,i)%Mod+Mod)%Mod;
			}
			printf("%d\n",Ans);
		}
	}
	/*
	O(1)
	限位排列 
	f[3]=1;f[4]=2;
	for(int i=5;i<=n;i++){
		if(i%2==0)f[i]=(1ll*f[i-1]*i%Mod+(1ll*f[i-2]*i-4+Mod)%Mod*inv[i-2]%Mod)%Mod;
		if(i%2==1)f[i]=(1ll*f[i-1]*i%Mod+(1ll*f[i-2]*i+4+Mod)%Mod*inv[i-2]%Mod)%Mod;
	}
	for(int i=1;i<=m;i++)printf("%d\n",f[q[i]]);
	*/
	return 0;
}