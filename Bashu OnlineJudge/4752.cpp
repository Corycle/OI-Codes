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
const int Mod=1e9+7;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,d,f[N],a[N][N],ans[N];
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
void Gauss(int n){
	for(int i=1;i<=n;i++){
		int t=i;
		for(int j=i;j<=n;j++)if(a[j][i])t=i;
		if(t!=i)swap(a[i],a[t]);
		if(!a[i][i])continue;
		int inv=Pow(a[i][i],Mod-2);
		for(int j=i+1;j<=n;j++){
			int dlt=1ll*a[j][i]*inv%Mod;
			for(int k=i;k<=n+1;k++){
				a[j][k]=mod(a[j][k]-1ll*a[i][k]*dlt%Mod+Mod);
			}
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=i+1;j<=n;j++){
			a[i][n+1]=mod(a[i][n+1]-1ll*a[i][j]*f[j-1]%Mod+Mod);
		}
		f[i-1]=1ll*a[i][n+1]*Pow(a[i][i],Mod-2)%Mod;
	}
}
void Prepare(){
	for(int i=1;i<=d+2;i++){
		for(int j=1;j<=d+2;j++)a[i][j]=Pow(i,j-1);
		a[i][d+3]=mod(a[i-1][d+3]+Pow(i,d));
	}
	Gauss(d+2);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	d=read();m=read();Prepare();
	for(int i=0;i<=d+1;i++)ans[i]=1;
	while(m--){
		int p=read(),k=read();
		int pk=Pow(p,k),pd=Pow(p,d),inv=Pow(p,Mod-2);
		for(int i=0;i<=d+1;i++){
			ans[i]=1ll*ans[i]*mod(Pow(pk,i)-1ll*pd*Pow(1ll*pk*inv%Mod,i)%Mod+Mod)%Mod;
		}
	}
	int Ans=0;
	for(int i=0;i<=d+1;i++)Ans=mod(Ans+1ll*f[i]*ans[i]%Mod);
	printf("%d",Ans);
	return 0;
}