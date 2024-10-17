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
const int M=(1<<12)+5;
const int MaxN=205;
const int N=13;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,P,cnt,Ans;
int a[N],b[M],sta[N],pos[N],F[N][N][M],G[MaxN][MaxN];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();P=read();
	for(int i=1;i<=P;i++){int num=read();while(num--)a[i]|=(1<<(read()-1));}
	for(int i=1;i<=P;i++)b[a[i]]+=read();
	for(int i=1;i<=m;i++)pos[i]=read();
	int Num=read();
	memset(F,0x3f,sizeof(F));memset(G,0x3f,sizeof(G));for(int i=1;i<=n;i++)G[i][i]=0;
	for(int i=1;i<=Num;i++){int x=read(),y=read();G[x][y]=G[y][x]=min(G[x][y],read());}
	for(int i=1;i<=m;i++){int num=read();while(num--)sta[i]|=(1<<(read()-1));}
	int st=read(),Sta=(1<<m)-1;
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
			}
		}
	}
	for(int i=1;i<=m;i++){
		if(!sta[i]){
			int S=(1<<(i-1));
			if(K)F[i][K-1+b[S]][S]=0;
			F[i][K+b[S]][S]=G[st][pos[i]];
		}
	}
	for(int S=0;S<=Sta;S++){
		for(int y=1;y<=m;y++){
			if(((S>>(y-1))&1)||((sta[y]|S)!=S))continue;
			int T=S|(1<<(y-1)),num=0;
			for(int tmp=S;;tmp=(tmp-1)&S){num+=b[tmp|(1<<(y-1))];if(!tmp)break;}
			for(int k=0;k<=12;k++){
				for(int x=1;x<=m;x++){
					if(F[x][k][S]==inf)continue;
					if(k)F[y][k-1+num][T]=min(F[y][k-1+num][T],F[x][k][S]);
					F[y][k+num][T]=min(F[y][k+num][T],F[x][k][S]+G[pos[x]][pos[y]]);
				}
			}
		}
	}
	Ans=inf;
	for(int x=1;x<=m;x++)for(int k=0;k<=12;k++)Ans=min(Ans,F[x][k][Sta]);
	printf("%d\n",Ans);
	return 0;
}
