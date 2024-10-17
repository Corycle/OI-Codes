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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,Sum,a[N],fac[N],inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
struct Tree{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Clear(){for(int i=1;i<=n;i++)c[i]=0;}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]=mod(c[x]+y);}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans=mod(ans+c[x]);return ans;}
	int Query(int l,int r){return mod(Ask(r)-Ask(l-1)+Mod);}
}tree;
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int Sqr(int x){return 1ll*x*x%Mod;}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare();
	for(int i=1;i<=n;i++){
		a[i]=read();m+=(a[i]==-1);
		if(a[i]!=-1){Ans=mod(Ans+tree.Query(a[i],n));tree.Add(a[i],1);}
	}
	Ans=mod(Ans+1ll*Sqr(C(m,2))*(m>=2?fac[m-2]:1)%Mod*inv[m]%Mod);
	for(int i=1,num=0;i<=n;i++){
		if(a[i]==-1){num++;continue;}
		Sum=mod(Sum+1ll*(m-num)*(a[i]-tree.Query(1,a[i]))%Mod);
		Sum=mod(Sum+1ll*num*(n-a[i]+1-tree.Query(a[i],n))%Mod);
	}
	Ans=mod(Ans+1ll*Sum*fac[m-1]%Mod*inv[m]%Mod);
	printf("%d\n",Ans);
	return 0;
}
