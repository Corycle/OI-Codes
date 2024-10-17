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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,B,Ans;
int a[N],Pow[N],sum[N],f[N][N][2],g[N][N][2];
void Prepare(){
	int maxn=1000;Pow[0]=sum[0]=1;
	for(int i=1;i<=maxn;i++)Pow[i]=1ll*Pow[i-1]*B%Mod;
	for(int i=1;i<=maxn;i++)sum[i]=(sum[i-1]+Pow[i])%Mod;
}
void Solve(int b){
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	f[0][0][1]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			for(int t=0;t<=1;t++){
				int p=t?a[i+1]:B-1;
				int F=f[i][j][t],G=g[i][j][t];
				for(int k=0;k<=p;k++){
					int tmp=(1ll*F*k%Mod+1ll*G*B%Mod)%Mod;
					f[i+1][j+(k>=b)][t&(k==p)]=(f[i+1][j+(k>=b)][t&(k==p)]+F)%Mod;
					g[i+1][j+(k>=b)][t&(k==p)]=(g[i+1][j+(k>=b)][t&(k==p)]+tmp)%Mod;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)Ans=(Ans+1ll*(g[n][i][0]+g[n][i][1])%Mod*sum[i-1]%Mod)%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();B=read();Prepare();
	while(T--){
		scanf("%s",s+1);n=strlen(s+1);Ans=0;
		for(int i=1;i<=n;i++)a[i]=s[i]-'0';
		for(int b=1;b<B;b++)Solve(b);
		printf("%d\n",Ans);
	}
	return 0;
}