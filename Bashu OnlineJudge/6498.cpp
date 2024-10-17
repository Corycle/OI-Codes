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
const int N=1<<15;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,p[N],f[N],g[N],num[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();read();
	int Sta=(1<<n)-1;p[0]=1;
	for(int i=1;i<=m;i++)p[i]=mod(p[i-1]<<1);
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		for(int S=0;S<=Sta;S++){
			if(((S>>(x-1))&1)&&((S>>(y-1))&1))num[S]++;
		}
	}
	f[1]=1;
	for(int S=2;S<=Sta;S++){
		if(S&1){
			f[S]=p[num[S]];
			for(int T=(S-1)&S;T;T=(T-1)&S){
				f[S]=mod(f[S]-1ll*f[T]*p[num[S^T]]%Mod+Mod);
			}
		}
	}
	g[2]=1;
	for(int S=3;S<=Sta;S++){
		if(S&2){
			g[S]=p[num[S]];
			for(int T=(S-1)&S;T;T=(T-1)&S){
				g[S]=mod(g[S]-1ll*g[T]*p[num[S^T]]%Mod+Mod);
			}
		}
	}
	Ans=p[m];
	for(int i=0;i<=Sta;i++){
		for(int T=i;T;T=(T-1)&i){
			int S=Sta^i;
			if(!(S&1)||!(T&2))continue;
			if(num[S|T]==num[S]+num[T]){
				Ans=mod(Ans-1ll*f[S]*g[T]%Mod*p[num[Sta^(S|T)]]%Mod+Mod);
			}
		}
	}
	printf("%d",Ans);
	return 0;
}