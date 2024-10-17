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
const int Phi=998244352;
const int N=500005;
const int G=3;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,len,L,R[N],f[N],g[N],fac[N],inv[N];
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=n;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=n;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=n;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void NTT(int a[],int n,int f){
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<n;i<<=1){
		int Wn=Pow(G,Phi+f*Phi/(i<<1));
		for(int j=0;j<n;j+=(i<<1)){
			int W=1;
			for(int k=0;k<i;k++){
				int x=a[j+k],y=1ll*W*a[j+k+i]%Mod;
				W=1ll*W*Wn%Mod;
				a[j+k]=(x+y)%Mod;
				a[j+k+i]=(x-y+Mod)%Mod;
			}
		}
	}
	if(f==-1){
		int Inv=Pow(n,Mod-2);
		for(int i=0;i<n;i++)a[i]=1ll*a[i]*Inv%Mod;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare();
	for(int i=0;i<=n;i++){
		f[i]=1ll*read()*inv[i]%Mod*inv[n-i]%Mod;
		if((n-i)&1)f[i]=Mod-f[i];
	}
	for(int i=0;i<=n+n;i++)g[i]=Pow(m-n+i,Mod-2);
	len=1;L=0;while(len<=n+n){len<<=1;L++;}
	for(int i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	NTT(f,len,1);NTT(g,len,1);
	for(int i=0;i<len;i++)f[i]=1ll*f[i]*g[i]%Mod;
	NTT(f,len,-1);
	int tmp=1;
	for(int i=0;i<=n;i++)f[i]=f[i+n];
	for(int i=n+1;i<len;i++)f[i]=0;
	for(int i=m-n;i<=m;i++)tmp=1ll*tmp*i%Mod;
	for(int i=0;i<=n;i++){
		int Ans=1ll*tmp*f[i]%Mod;
		tmp=1ll*tmp*Pow(m-n+i,Mod-2)%Mod*(m+i+1)%Mod;
		printf("%d ",Ans);
	}
	return 0;
}