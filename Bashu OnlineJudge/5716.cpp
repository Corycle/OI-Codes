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
const ll inf=9e18;
const int N=10005;
const int M=32;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,A[N],B[N];
int a[M][N],b[M][N],c[M][N],d[M][N];
ll g1[N][M][M],g2[N][M],f[N][M][M];
int Calc1(int p,int num,int S){
	int ans=0;
	for(int i=1;i<=n;i++){
		A[i]=(S>>(i-1))&1;
		B[i]=(a[i][p]>>num)&1;
	}
	A[n+1]=A[1];
	for(int i=1;i<=n;i++){
		ans+=(A[i]^B[i])*b[i][p];
		ans+=(A[i]^A[i+1])*d[i][p];
	}
	return ans;
}
int Calc2(int p,int S){
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=((S>>(i-1))&1)*c[i][p];
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)b[i][j]=read();
	for(int i=1;i<=n;i++)for(int j=1;j<m;j++)c[i][j]=read();
	for(int i=1;i<n;i++)for(int j=1;j<=m;j++)d[i][j]=read();
	for(int i=1;i<=m;i++)d[n][i]=read();
	int Sta=(1<<n)-1;
	for(int i=1;i<=m;i++){
		for(int j=0;j<=20;j++){
			for(int S=0;S<=Sta;S++){
				g1[i][j][S]=Calc1(i,j,S);
				f[i][j][S]=(i==1?g1[i][j][S]:inf);
			}
		}
	}
	for(int i=1;i<m;i++){
		for(int S=0;S<=Sta;S++){
			g2[i][S]=Calc2(i,S);
		}
	}
	for(int i=2;i<=m;i++){
		for(int j=0;j<=20;j++){
			for(int S=0;S<=Sta;S++){
				for(int T=0;T<=Sta;T++){
					f[i][j][S]=min(f[i][j][S],f[i-1][j][T]+g1[i][j][S]+g2[i-1][S^T]);
				}
			}
		}
	}
	ll Ans=0;
	for(int i=0;i<=20;i++){
		ll Min=inf;
		for(int S=0;S<=Sta;S++){
			Min=min(Min,f[m][i][S]);
		}
		Ans+=(1ll<<i)*Min;
	}
	printf("%lld",Ans);
	return 0;
}