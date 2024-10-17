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
const int N=605;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,K,Ans,g[N],b[N],sum[N],f[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Sum(int l,int r){return sum[r]-sum[l-1];}
void Solve(int l,int r){
	for(int i=l;i<=r;i++)if(b[i]&&(b[i]<l||b[i]>r))return;
	f[l][r]=g[Sum(l,r)>>1];
	for(int x=l+1;x<r;x++){
		f[l][r]=mod(f[l][r]-1ll*f[l][x]*g[Sum(x+1,r)>>1]%Mod+Mod);
	}
	Ans=mod(Ans+1ll*f[l][r]*g[(Sum(1,l-1)+Sum(r+1,n*2))>>1]%Mod);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();g[0]=1;
	for(int i=1;i<=n;i++)g[i]=1ll*g[i-1]*(2*i-1)%Mod;
	for(int i=1;i<=K;i++){int x=read(),y=read();b[b[x]=y]=x;}
	for(int i=1;i<=n*2;i++)sum[i]=sum[i-1]+(!b[i]);
	for(int l=1;l<=n*2;l++){
		for(int r=l+1;r<=n*2;r++){
			if(!(Sum(l,r)&1)&&!((r-l+1)&1))Solve(l,r);
		}
	}
	printf("%d",Ans);
	return 0;
}