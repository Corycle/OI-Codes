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
const int N=7505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,f[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){int ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();scanf("%s",s+1);m=strlen(s+1);
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=m+n/2;j>=0;j--){
			f[i][j]=mod(f[i][j]+f[i-1][j+1]);
			if(!j)f[i][j]=mod(f[i][j]+f[i-1][j]);
			if(j)f[i][j]=mod(f[i][j]+f[i-1][j-1]*2%Mod);
		}
	}
	printf("%lld\n",1ll*f[n][m]*Pow(Pow(2,m),Mod-2)%Mod);
	return 0;
}
