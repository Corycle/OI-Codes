/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
const int N=1e5+5;
const int M=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[M][M];
int n,m,Q,Ans[N],f[M][M],sum[M][M],s1[M][M],s2[M][M];
struct Node{int sx,sy,tx,ty,Lim;}P[N];
int S1(int sx,int sy,int tx,int ty){return s1[tx][ty]+s1[sx-1][sy-1]-s1[tx][sy-1]-s1[sx-1][ty];}
int S2(int sx,int sy,int tx,int ty){return s2[tx][ty]+s2[sx-1][sy-1]-s2[tx][sy-1]-s2[sx-1][ty];}
int Sum(int sx,int sy,int tx,int ty){return sum[tx][ty]+sum[sx-1][sy-1]-sum[tx][sy-1]-sum[sx-1][ty];}
bool Check(int x,int y,int l){
	if(l==1)return true;
	return (S1(x-l+1,y-l+2,x,y)==l*(l-1))&&(S2(x-l+2,y-l+1,x,y)==l*(l-1));
}
int main(){
//	freopen("square.in","r",stdin);
//	freopen("square.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			s1[i][j]=s1[i][j-1]+(a[i][j]>=a[i][j-1]);
			s2[i][j]=s2[i][j-1]+(a[i][j]>=a[i-1][j]);
		}
		for(int j=1;j<=m;j++){
			s1[i][j]+=s1[i-1][j];s2[i][j]+=s2[i-1][j];
			for(int k=1;k<=min(i,j);k++)if(Check(i,j,k))f[i][j]=k;
		}
	}
	Q=read();
	for(int i=1;i<=Q;i++){
		P[i].sx=read();P[i].sy=read();P[i].tx=read();P[i].ty=read();
		P[i].Lim=min(P[i].tx-P[i].sx+1,P[i].ty-P[i].sy+1);
	}
	for(int t=1;t<=min(n,m);t++){
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+(f[i][j]>=t);
		for(int i=1;i<=Q;i++)if(t<=P[i].Lim&&Sum(P[i].sx+t-1,P[i].sy+t-1,P[i].tx,P[i].ty))Ans[i]=t;
	}
	for(int i=1;i<=Q;i++)printf("%d\n",Ans[i]);
	return 0;
}