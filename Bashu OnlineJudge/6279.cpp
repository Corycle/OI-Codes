/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=155;
const int M=35;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,len[M];
char S[N],s[M][M];
int f[N][N][M][M],g[N][N],Ans[N][N];
int main(){
//	freopen("string.in","r",stdin);
//	freopen("string.out","w",stdout);
	scanf("%s",S+1);
	n=strlen(S+1);m=read();
	for(int i=1;i<=m;i++){
		scanf("%s",s[i]+1);
		len[i]=strlen(s[i]+1);
	}
	for(int i=n;i>=1;i--){
		for(int j=i;j<=n;j++){
			for(int k=1;k<=m;k++){
				if(i==j)f[i][j][k][1]|=(S[j]==s[k][1]);
				else{
					for(int l=1;l<=len[k];l++){
						f[i][j][k][l]|=(f[i][j-1][k][l-1]&(S[j]==s[k][l]));
						for(int t=i;t<=j;t++){
							f[i][j][k][l]|=(f[i][t][k][l]&g[t+1][j]);
						}
					}
				}
				g[i][j]|=f[i][j][k][len[k]];
			}
		}
	}
	for(int t=1;t<=n;t++){
		for(int i=1;i+t-1<=n;i++){
			int j=i+t-1;
			Ans[i][j]=g[i][j]?0:j-i+1;
			for(int k=i;k<j;k++){
				Ans[i][j]=min(Ans[i][j],Ans[i][k]+Ans[k+1][j]);
			}
		}
	}
	printf("%d\n",Ans[1][n]);
	return 0;
}