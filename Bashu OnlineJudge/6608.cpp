/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
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
const int N=1e3+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,X,Ans,Mod;
int a[N],b[N],S[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int F(int n,int k){
	int ans=1;
	for(int i=n-k+1;i<=n;i++)ans=1ll*ans*i%Mod;
	return ans;
}
int main(){
//	freopen("problem.in","r",stdin);
//	freopen("problem.out","w",stdout);
	n=read();X=read();Mod=read();m=read();
	for(int i=0;i<=m;i++)a[i]=read();
	S[0][0]=1;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=i;j++){
			S[i][j]=mod(S[i-1][j-1]+1ll*j*S[i-1][j]%Mod);
		}
	}
	for(int i=0;i<=m;i++){
		for(int j=i;j<=m;j++){
			b[i]=mod(b[i]+1ll*S[j][i]*a[j]%Mod);
		}
	}
	for(int i=0;i<=m;i++){
		Ans=mod(Ans+1ll*b[i]*Pow(X,i)%Mod*Pow(X+1,n-i)%Mod*F(n,i)%Mod);
	}
	printf("%d",Ans);
	return 0;
}