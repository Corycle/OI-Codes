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
const int Mod=1e9+9;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,num[N],f[N][N],C[N][N],fac[N],inv[N];
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
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
	for(int i=0;i<N;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare();
	for(int i=1;i<=n;i++)num[read()]++;
	int Ans=0;f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=num[i]&&k<=j;k++){
				f[i][j]=mod(f[i][j]+1ll*f[i-1][j-k]*C[num[i]][k]%Mod*inv[num[i]-k]%Mod);
			}
		}
	}
	for(int i=0;i<=n;i++){
		int t=(i&1)?-1:1;
		Ans=(Ans+1ll*t*f[n][i]%Mod*fac[n-i]%Mod)%Mod;
	}
	printf("%d",(Ans%Mod+Mod)%Mod);
	return 0;
}