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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,c,Ans,C[N][N];
void Prepare(int maxn){
	C[0][0]=1;
	for(int i=1;i<=maxn;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
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
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare(500);
	n=read();m=read();c=read();
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int k=0;k<=c;k++){
				Ans=(Ans+1ll*((i+j+k)&1?-1:1)*C[n][i]%Mod*C[m][j]%Mod*C[c][k]%Mod*Pow(c-k+1,(n-i)*(m-j))%Mod+Mod)%Mod;
			}
		}
	}
	printf("%d",Ans);
	return 0;
}