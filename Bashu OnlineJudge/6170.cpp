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
const int N=50005;
const int M=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int S[N][M],C[N][M];
void Prepare(){
	int n=5e4,m=2e2;
	C[0][0]=1;
	for(int i=1;i<=m;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
		}
	}
	S[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			S[i][j]=(S[i-1][j-1]+1ll*S[i-1][j]*(i-1)%Mod)%Mod;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare();
	int T=read();
	while(T--){
		int n=read(),A=read(),B=read();
		printf("%lld\n",1ll*C[A+B-2][A-1]*S[n-1][A+B-2]%Mod);
	}
	return 0;
}