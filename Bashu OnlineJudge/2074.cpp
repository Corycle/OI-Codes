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
const int Mod=2004;
const int N=11;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,L,R,Fac,Sta,Ans,a[N];
int C(int n,int m){
	if(n<m)return 0;
	ll mod=1ll*Fac*Mod,ans=1;
	for(int i=n-m+1;i<=n;i++)ans=ans*i%mod;
	return ans/Fac;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();L=read();R=read();
	Fac=1;Sta=(1<<n)-1;
	for(int i=1;i<=n;i++)Fac=Fac*i;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int S=0;S<=Sta;S++){
		int num=0,tmp=0;
		for(int i=1;i<=n;i++)if((S>>(i-1))&1){num++;tmp+=a[i]+1;}
		Ans=(Ans+(num&1?-1:1)*(C(R-tmp+n,n)-C(L-1-tmp+n,n)))%Mod;
	}
	Ans=(Ans%Mod+Mod)%Mod;
	printf("%d",Ans);
	return 0;
}