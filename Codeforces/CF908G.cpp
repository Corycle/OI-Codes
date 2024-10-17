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
const int N=705;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,Ans,a[N],P[N],f[N][N][10][2];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++)a[i]=s[i]-'0';
	for(int i=0;i<=9;i++)f[0][0][i][1]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			for(int k=0;k<=9;k++){
				for(int p=0;p<2;p++){
					int Max=(p?a[i]:9);
					for(int l=0;l<=Max;l++){
						f[i][j+(l>=k)][k][p&(l==Max)]=mod(f[i][j+(l>=k)][k][p&(l==Max)]+f[i-1][j][k][p]);
					}
				}
			}
		}
	}
	P[1]=1;
	for(int i=2;i<=n;i++)P[i]=1ll*P[i-1]*10%Mod;
	for(int i=2;i<=n;i++)P[i]=mod(P[i]+P[i-1]);
	for(int i=1;i<=n;i++){
		for(int k=1;k<=9;k++){
			Ans=mod(Ans+1ll*P[i]*mod(f[n][i][k][0]+f[n][i][k][1])%Mod);
		}
	}
	printf("%d\n",Ans);
	return 0;
}
