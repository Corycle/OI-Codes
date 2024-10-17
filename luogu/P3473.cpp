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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N][N];
int n,m,Mod,Ex,Ey;
int L[N][N],U[N][N],f[2][4][N][N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int F(int x,int y){return x==Ex&&y==Ey;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Mod=read();Ey=read();Ex=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++){
			U[i][j]=U[i-1][j]+(s[i][j]=='*');
			L[i][j]=L[i][j-1]+(s[i][j]=='*');
		}
	}
	int t=0;
	for(int S=2;S<=n+m;S++){
		t^=1;
		memset(f[t],0,sizeof(f[t]));
		for(int i=1;i<=n&&i<S;i++){
			int j=S-i;
			for(int sx=1;sx<=Ex&&sx+i-1<=n;sx++){
				for(int sy=1;sy<=Ey&&sy+j-1<=m;sy++){
					int tx=sx+i-1,ty=sy+j-1;
					if(tx<Ex||ty<Ey)continue;
					f[t][0][sx][sy][tx]=mod(f[t^1][0][sx][sy][tx]+(L[sx][sy-1]==L[sx][ty])*(f[t^1][1][sx+1][sy][tx]+F(sx,ty)));
					f[t][1][sx][sy][tx]=mod(f[t^1][1][sx][sy][tx-1]+(U[sx-1][ty]==U[tx][ty])*(f[t^1][2][sx][sy][tx]+F(tx,ty)));
					f[t][2][sx][sy][tx]=mod(f[t^1][2][sx][sy+1][tx]+(L[tx][sy-1]==L[tx][ty])*(f[t^1][3][sx][sy][tx-1]+F(tx,sy)));
					f[t][3][sx][sy][tx]=mod(f[t^1][3][sx+1][sy][tx]+(U[sx-1][sy]==U[tx][sy])*(f[t^1][0][sx][sy+1][tx]+F(sx,sy)));
				}
			}
		}
	}
	printf("%d\n",f[t][3][1][1][n]);
	return 0;
}
