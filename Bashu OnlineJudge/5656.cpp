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
const int M=1024;
const int N=45;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,c,Sta,pos[M],num[M];
int P[N][N][4],g[N][M][N],f[N][M][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int lowbit(int x){return x&(-x);}
int main(){
//	freopen("max.in","r",stdin);
//	freopen("max.out","w",stdout);
	n=read();m=read();c=read();
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			for(int k=0;k<=c;k++){
				P[i][j][k]=read();
			}
		}
	}
	Sta=(1<<m)-1;
	for(int i=1;i<=m;i++)pos[1<<(i-1)]=i;
	for(int i=1;i<=Sta;i++)num[i]=num[i>>1]+(i&1);
	for(int i=1;i<=n;i++){
		g[i][0][0]=1;
		for(int S=1;S<=Sta;S++){
			int T=S^lowbit(S);
			for(int j=0;j<=num[T]*c;j++){
				for(int k=0;k<=c;k++){
					g[i][S][j+k]=mod(g[i][S][j+k]+1ll*g[i][T][j]*P[pos[S-T]][i][k]%Mod);
				}
			}
		}
	}
	f[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int S=0;S<=Sta;S++){
			for(int T=S;;T=(T-1)&S){
				for(int j=0;j<=num[S-T]*c;j++){
					for(int k=0;k<=num[T]*c;k++){
						int Max=max(j,k);
						f[i][S][Max]=mod(f[i][S][Max]+1ll*f[i-1][T][k]*g[i][S-T][j]%Mod);
					}
				}
				if(!T)break;
			}
		}
	}
	int Ans=0;
	for(int i=0;i<=m*c;i++){
		Ans=mod(Ans+1ll*f[n][Sta][i]*i%Mod);
	}
	printf("%d",Ans);
	return 0;
}