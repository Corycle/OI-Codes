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
const int Inv100=570000004;
const int Mod=1000000007;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,f[N],g[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	f[0]=1;
	for(int i=1;i<=n;i++){
		int a=1ll*read()*Inv100%Mod;
		int b=1ll*read()*Inv100%Mod;
		int tmp=Pow(mod(1-1ll*g[i-1]*b%Mod+Mod),Mod-2);
		g[i]=mod(b+1ll*g[i-1]*a%Mod*a%Mod*tmp%Mod);
		f[i]=1ll*f[i-1]*a%Mod*tmp%Mod;
	}
	printf("%d",f[n]);
	return 0;
}