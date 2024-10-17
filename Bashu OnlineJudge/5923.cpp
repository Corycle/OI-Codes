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
const int N=55;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],f[N][N],C[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Solve(int l,int r){
	if(l==r)return 1;
	if(r==l+1)return (a[l]==r&&a[r]==l);
	if(f[l][r]!=-1)return f[l][r];
	int ans=0;
	for(int i=l;i<r;i++){
		swap(a[i],a[i+1]);
		int flag=1;
		for(int j=l;j<=i;j++)flag&=(a[j]<=i);
		for(int j=i+1;j<=r;j++)flag&=(a[j]>i);
		if(flag)ans=mod(ans+1ll*Solve(l,i)*Solve(i+1,r)%Mod*C[r-l-1][i-l]%Mod)%Mod;
		swap(a[i],a[i+1]);
	}
	return f[l][r]=ans;
}
int main(){
//	freopen("swap.in","r",stdin);
//	freopen("swap.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read()+1;
	for(int i=0;i<N;i++){C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=mod(C[i-1][j]+C[i-1][j-1]);}
	memset(f,-1,sizeof(f));
	printf("%d\n",Solve(1,n));
	return 0;
}