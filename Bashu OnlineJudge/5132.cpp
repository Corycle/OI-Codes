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
const int Mod=1000007;
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N],f[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)f[n+1][i]=1;
	for(int i=n;i>=1;i--){
		for(int j=1;j<=i;j++){
			f[i][j]=mod(f[i][j]+1ll*j*f[i+1][j]%Mod+f[i+1][j+1]);
		}
	}
	int Max=0,Ans=0;
	for(int i=1;i<=n;i++){
		Ans=mod(Ans+1ll*(a[i]-1)*f[i+1][Max]%Mod);
		Max=max(Max,a[i]);
	}
	printf("%d",Ans+1);
	return 0;
}