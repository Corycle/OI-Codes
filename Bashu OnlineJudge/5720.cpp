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
const int N=300005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int L[N],f[N][M],g[N][M];
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int Ask(int l,int x){
	if(L[x]<=l)return x-l;
	int ans=x-L[x],tot=1;x=L[x];
	for(int k=(int)(log(n)/log(2));k>=0;k--){
		if(l<=f[x][k]){
			ans+=tot*(x-f[x][k])+g[x][k];
			tot+=(1<<k);x=f[x][k];
		}
	}
	if(l<x)ans+=tot*(x-l)+x-l;
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=2;i<=n;i++)L[i]=read();
	f[n][0]=L[n];g[n][0]=n-L[n];
	for(int i=n-1;i>=2;i--){
		f[i][0]=min(f[i+1][0],L[i]);
		g[i][0]=i-f[i][0];
	}
	int k=(int)(log(n)/log(2));
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(f[i][j-1]){
				f[i][j]=f[f[i][j-1]][j-1];
				g[i][j]=g[f[i][j-1]][j-1]+g[i][j-1]+(1<<(j-1))*(f[i][j-1]-f[i][j]);
			}
		}
	}
	m=read();
	while(m--){
		int l=read(),r=read(),x=read();
		int A=Ask(l,x)-Ask(r+1,x),B=r-l+1;
		int Gcd=gcd(A,B);A/=Gcd;B/=Gcd;
		printf("%d/%d\n",A,B);
	}
	return 0;
}