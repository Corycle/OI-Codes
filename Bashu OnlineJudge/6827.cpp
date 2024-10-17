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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,Ans;
int a[N],f[N][12];
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
	n=read();K=n-read()+1;m=read();
	f[0][0]=1;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=m;j>=a[i];j--){
			for(int k=K;k>=1;k--){
				f[j][k]=mod(f[j][k]+mod(f[j-a[i]][k-1]-f[j-a[i]][k]+Mod));
			}
		}
	}
	for(int i=1;i<=m;i++)Ans=mod(Ans+1ll*f[i][K]*Pow(i,Mod-2)%Mod);
	Ans=1ll*Ans*m%Mod;
	printf("%d",Ans);
	return 0;
}