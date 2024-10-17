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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Mod,Sum,F[N],Fac[N],Inv[N],inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	Fac[0]=Fac[1]=Inv[0]=Inv[1]=inv[0]=inv[1]=1;
	for(int i=2;i<N&&i<Mod;i++)Fac[i]=1ll*Fac[i-1]*i%Mod;
	for(int i=2;i<N&&i<Mod;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<N&&i<Mod;i++)Inv[i]=1ll*Inv[i-1]*inv[i]%Mod;
}
int main(){
//	freopen("array.in","r",stdin);
//	freopen("array.out","w",stdout);
	n=read();Mod=read();Prepare();
	for(int i=3;i<=n;i++){
		F[i]=1ll*mod(2ll*Sum%Mod+1ll*(i+1)*(i-2)%Mod*inv[2]%Mod)*inv[i]%Mod;
		Sum=mod(Sum+F[i]);
	}
	int Ans=1ll*F[n]*Fac[n]%Mod;
	printf("%d\n",Ans);
	return 0;
}