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
const int Mod=1e9+3;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,K;
int a[N],f[N][2];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(1){
		int Ans=0;
		n=read();K=read();if(!n)break;
		for(int i=1;i<=n;i++)a[i]=read();
		for(int k=30;k>=0;k--){
			memset(f,0,sizeof(f));
			f[0][0]=1;
			for(int i=1;i<=n;i++){
				if((a[i]>>k)&1){
					f[i][0]=(f[i][0]+1ll*f[i-1][0]*(1<<k)%Mod)%Mod;//Choose 0
					f[i][1]=(f[i][1]+1ll*f[i-1][1]*(1<<k)%Mod)%Mod;//Choose 0
					f[i][0]=(f[i][0]+1ll*f[i-1][1]*((a[i]^(1<<k))+1)%Mod)%Mod;//Choose 1
					f[i][1]=(f[i][1]+1ll*f[i-1][0]*((a[i]^(1<<k))+1)%Mod)%Mod;//Choose 1
				}
				else{
					f[i][0]=(f[i][0]+1ll*f[i-1][0]*(a[i]+1)%Mod)%Mod;//Choose 0
					f[i][1]=(f[i][1]+1ll*f[i-1][1]*(a[i]+1)%Mod)%Mod;//Choose 0
				}
			}
			int sum=1,t=(K>>k)&1;
			for(int i=n;i>=1;i--){
				int w=(a[i]>>k)&1;
				if(w){
					Ans=(Ans+1ll*sum*f[i-1][t]%Mod)%Mod;
					//i Choose 0 ; 1 ~ i-1 Choose t ; i+1 ~ n Choose Max
					a[i]^=(1<<k);
				}
				//i Choose Max
				t^=w;sum=1ll*sum*(a[i]+1)%Mod;
			}
			if(t)break;
			if(!k)Ans=(Ans+1)%Mod;
		}
		printf("%d\n",Ans);
	}
	return 0;
}