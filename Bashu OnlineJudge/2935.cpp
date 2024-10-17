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
const int N=1<<18;
const int M=8;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bool vis[N][M][3][3];
int n,tot,sta[3],id[3][M];
double Ans,P[3][3][M][M],F[N][M][3][3];
double DFS(int S,int pos,int x,int y){
	if(!S)return (x==0);
	if(vis[S][pos][x][y])return F[S][pos][x][y];
	int num=0,k=(S&sta[3-x-y])?3-x-y:y;// x and k
	double ans=(k==0)?0:inf;
	for(int i=1;i<=n-1;i++){
		if(S&(1<<id[k][i])){
			int T=S^(1<<id[k][i]);num++;
			if(k)ans=min(ans,P[x][k][pos][i]*DFS(T,pos,x,k)+P[k][x][i][pos]*DFS(T,i,k,x));
			else ans=max(ans,P[x][k][pos][i]*DFS(T,pos,x,k)+P[k][x][i][pos]*DFS(T,i,k,x));
		}
	}
	if(!num)ans=(x==0?1:0);
	vis[S][pos][x][y]=1;
	F[S][pos][x][y]=ans;
	return F[S][pos][x][y];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=0;i<3;i++){
		for(int j=i+1;j<3;j++){
			for(int a=1;a<=n;a++){
				for(int b=1;b<=n;b++){
					scanf("%lf",&P[i][j][a][b]);
					P[j][i][b][a]=1-P[i][j][a][b];
				}
			}
		}
	}
	for(int i=0;i<3;i++){
		for(int j=1;j<n;j++){
			id[i][j]=tot++;
			sta[i]|=(1<<id[i][j]);
		}
	}
	int S=(1<<(3*(n-1)))-1;
	Ans+=(P[0][2][n][n]+P[1][2][n][n])*P[0][1][n][n]*DFS(S,n,0,1);// 0 win 2 || 1 win 2 -> 0 and 1 -> 0 win 1
//	cout<<Ans<<endl;
	Ans+=(P[0][2][n][n]+P[1][2][n][n])*P[1][0][n][n]*DFS(S,n,1,0);// 0 win 2 || 1 win 2 -> 0 and 1 -> 1 win 0
//	cout<<Ans<<endl;
	Ans+=(P[0][1][n][n]+P[2][1][n][n])*P[0][2][n][n]*DFS(S,n,0,2);// 0 win 1 || 2 win 1 -> 0 and 2 -> 0 win 2
//	cout<<Ans<<endl;
	Ans+=(P[0][1][n][n]+P[2][1][n][n])*P[2][0][n][n]*DFS(S,n,2,0);// 0 win 1 || 2 win 1 -> 0 and 2 -> 2 win 0
//	cout<<Ans<<endl;
	Ans+=(P[1][0][n][n]+P[2][0][n][n])*P[1][2][n][n]*DFS(S,n,1,2);// 1 win 0 || 2 win 0 -> 1 and 2 -> 1 win 2
//	cout<<Ans<<endl;
	Ans+=(P[1][0][n][n]+P[2][0][n][n])*P[2][1][n][n]*DFS(S,n,2,1);// 1 win 0 || 2 win 0 -> 1 and 2 -> 2 win 1
//	cout<<Ans<<endl;
	printf("%.6lf",Ans/3);
	return 0;
}