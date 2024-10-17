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
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll s1[N][N],s2[N][N];
int n,m,K,Ans,a[N][N],b[N][N];
void Reverse(){
	swap(n,m);
	for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)b[i][j]=a[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=b[j][i];
}
void Prepare(){
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)s1[i][j]=s1[i][j-1]+a[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)s2[i][j]=s2[i-1][j]+a[i][j];
}
int Calc(int pos){
	ll dlt=0;
	int num=0,X1=1,X2=n,Y1=1,Y2=m;
	while(X1<=X2&&Y1<=Y2){
		num++;
		dlt=s1[X1][Y2]-s1[X1][Y1-1];if(dlt<=K){X1++;continue;}
		dlt=s1[X2][Y2]-s1[X2][Y1-1];if(dlt<=K){X2--;continue;}
		dlt=s2[X2][Y1]-s2[X1-1][Y1];if(dlt<=K&&Y1<=pos){Y1++;continue;}
		dlt=s2[X2][Y2]-s2[X1-1][Y2];if(dlt<=K&&Y2>=pos){Y2--;continue;}
		return inf;
	}
	return num;
}
void Solve(){
	Prepare();
	for(int i=0;i<=m;i++)Ans=min(Ans,Calc(i));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	K=read();m=read();n=read();Ans=inf;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=read();
	Solve();Reverse();Solve();
	printf("%d\n",Ans);
	return 0;
}
