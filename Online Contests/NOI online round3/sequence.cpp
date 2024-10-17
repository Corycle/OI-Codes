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
const int N=1e6+5;
const int M=262200;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt,Sta,Ans;
int a[N],num[M],phi[M],vis[M],prime[M],f[M];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(int maxn){
	phi[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;phi[i]=i-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])phi[i*prime[j]]=phi[i]*phi[prime[j]];
			else{phi[i*prime[j]]=phi[i]*prime[j];break;}
		}
	}
}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int lowbit(int x){return x&(-x);}
int main(){
//	freopen("sequence.in","r",stdin);
//	freopen("sequence.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		num[a[i]]++;
		Sta|=a[i];
	}
	Prepare(Sta+1);
	f[0]=Pow(2,num[0]);
	for(int S=1;S<=Sta;S++){
		int tmp=S^lowbit(S);
		for(int T=tmp;;T=(T-1)&tmp){
			f[S]=mod(f[S]+1ll*f[T]*num[S^T]%Mod);
			if(!T)break;
		}
	}
	for(int i=0;i<=Sta;i++)Ans=mod(Ans+1ll*f[i]*phi[i+1]%Mod);
	printf("%d",Ans);
	return 0;
}
