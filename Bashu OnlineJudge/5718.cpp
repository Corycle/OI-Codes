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
const int M=1048600;
const int N=21;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Sta,Ans;
int a[N],f[M][2],g[M],sum[M];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Sta=(1<<n)-1;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int S=0;S<=Sta;S++){
		for(int i=1;i<=n;i++){
			if((S>>(i-1))&1)sum[S]+=a[i];
		}
	}
	g[0]=f[0][1]=1;
	for(int S=0;S<=Sta;S++){
		for(int i=1;i<=n;i++){
			if(!((S>>(i-1))&1)){
				int T=S|(1<<(i-1));
				if(sum[T]<0)g[T]=(g[T]+g[S])%Mod;
				f[T][sum[T]>=0]=(f[T][sum[T]>=0]+f[S][1])%Mod;
			}
		}
	}
	for(int S=1;S<=Sta;S++){
		Ans=(Ans+1ll*sum[S]*g[Sta^S]%Mod*(f[S][0]+f[S][1])%Mod)%Mod;
	}
	printf("%d",(Ans%Mod+Mod)%Mod);
	return 0;
}