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
const int N=(1<<16)+5;
const int M=17;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Sta,Ans;
int a[M],f[2][N],fac[N],inv[N],num[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Sta=(1<<n)-1;
	for(int i=1;i<=m;i++)a[i]=read();
	int t=0;f[t][0]=1;Prepare();
	for(int i=m;i>=1;i--){
		t^=1;
		memcpy(f[t],f[t^1],sizeof(f[t]));
		for(int S=0;S<=Sta;S++){
			for(int j=0;j<n;j++){
				if((S>>j)&1)continue;
				int T=S|(1<<j);
				f[t][T]=mod(f[t][T]+1ll*f[t^1][S]*fac[1<<j]%Mod*C((1<<n)-S-a[i],(1<<j)-1)%Mod);
			}
		}
	}
	for(int S=0;S<=Sta;S++){
		num[S]=num[S>>1]+(S&1);
		Ans=mod(Ans+1ll*(num[S]&1?Mod-1:1)*f[t][S]%Mod*fac[Sta-S]%Mod);
	}
	Ans=1ll*Ans*(1<<n)%Mod;
	printf("%d",Ans);
	return 0;
}
