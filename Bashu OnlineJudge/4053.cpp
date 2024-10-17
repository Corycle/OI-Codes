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
const int N=5e4+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,phi[N],vis[N],prime[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Sum(int x){return 1ll*x*(x+1)/2%Mod;}
int F(int n,int T){
	int num=(n-1)/T;
	return 1ll*((n-T)+(n-num*T))*num/2%Mod;
}
void Prepare(int maxn){
	phi[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;phi[i]=i-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])phi[i*prime[j]]=1ll*phi[i]*phi[prime[j]]%Mod;
			else{phi[i*prime[j]]=1ll*phi[i]*prime[j]%Mod;break;}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare(5e4);
	int Ans=0,Min=min(n,m);
	for(int T=1;T<Min;T++){
		Ans=mod(Ans+1ll*F(n,T)*F(m,T)%Mod*phi[T]%Mod);
	}
	Ans=2ll*mod(Ans-1ll*Sum(n-1)*Sum(m-1)%Mod+Mod)%Mod;
	int t1=(1ll*n*(n-1)*(n-2)/6)%Mod;
	int t2=(1ll*m*(m-1)*(m-2)/6)%Mod;
	Ans=mod(Ans+mod(1ll*t1*m%Mod+1ll*t2*n%Mod));
	printf("%d",Ans);
	return 0;
}