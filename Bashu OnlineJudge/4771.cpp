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
const int M=132005;
const int N=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Sta;
int lowbit(int x){return x&(-x);}
int a[N][N],F[M],G[M],H[M],In[M],Out[M],num[M],cnt[M],Pow[M];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Out[1<<(x-1)]|=1<<(y-1);
		In[1<<(y-1)]|=1<<(x-1);
		a[x][y]=1;
	}
	Sta=(1<<n)-1;
	for(int S=1;S<=Sta;S++){
		for(int x=1;x<=n;x++){
			if(!((S>>(x-1))&1))continue;
			for(int y=1;y<=n;y++){
				if(!((S>>(y-1))&1))continue;
				H[S]+=a[x][y];
			}
		}
	}
	Pow[0]=1;
	for(int i=1;i<=m;i++)Pow[i]=(Pow[i-1]<<1)%Mod;
	for(int i=1;i<=Sta;i++)cnt[i]=cnt[i-lowbit(i)]+1;
	for(int S=1;S<=Sta;S++){
		int sta=S^lowbit(S);
		for(int T=sta;T;T=(T-1)&sta){
			G[S]=(G[S]-1ll*F[S-T]*G[T]%Mod+Mod)%Mod;
		}
		F[S]=Pow[H[S]];
		for(int T=S;T;T=(T-1)&S){
			if(S!=T){
				int u=lowbit(S-T);
				num[T]=num[T^u]+cnt[Out[u]&T]-cnt[In[u]&(S-T)];
			}
			F[S]=(F[S]-1ll*Pow[H[S-T]+num[T]]*G[T]%Mod+Mod)%Mod;
		}
		G[S]=(G[S]+F[S])%Mod;
	}
	printf("%d",F[Sta]);
	return 0;
}