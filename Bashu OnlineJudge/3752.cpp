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
const int Inv2=5e8+4;
const int Mod=1e9+7;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N][N];
int n,m,Sum,f[N][N][2];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Sum=1;
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=n;j++)if(s[i][j]=='.')Sum=mod(Sum<<1);
	}
	f[0][1][0]=f[1][0][1]=Sum;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			if(f[i][j][0]){
				f[i][j+1][0]=mod(f[i][j+1][0]+f[i][j][0]);
				if(s[i+1][j]=='.')f[i+1][j][1]=mod(f[i+1][j][1]+1ll*f[i][j][0]*Inv2%Mod);
			}
			if(f[i][j][1]){
				f[i+1][j][1]=mod(f[i+1][j][1]+f[i][j][1]);
				if(s[i][j+1]=='.')f[i][j+1][0]=mod(f[i][j+1][0]+1ll*f[i][j][1]*Inv2%Mod);
			}
		}
	}
	printf("%d\n",mod(f[n][n][0]+f[n][n][1]));
	return 0;
}
