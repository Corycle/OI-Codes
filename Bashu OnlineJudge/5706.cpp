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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p;
int C[N][N],f[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Ask(int p){
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=min(m,p+i-1);j++){
			for(int k=0;k<=j;k++){
				f[i][j]=mod(f[i][j]+1ll*f[i-1][j-k]*C[j][k]%Mod);
			}
		}
	}
	return f[n][m];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	for(int i=0;i<N;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=mod(C[i-1][j]+C[i-1][j-1]);
		}
	}
	printf("%d",mod(Ask(p)-Ask(p-1)+Mod));
	return 0;
}