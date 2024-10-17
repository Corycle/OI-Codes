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
int n,m,K,Ans,a[N][N],b[N][N];
void Reverse(){
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)b[i][j]=a[i][j];
	swap(n,m);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=b[j][i];
}
int Calc(int x,int y){
	int ans=0;
	for(int i=1;i<=n;i++)ans+=(a[i][x]==a[i][y]);
	return min(ans,n-ans);
}
void Solve(){
	for(int i=1;i<=m;i++){
		int Sum=0;
		for(int j=1;j<=m;j++)if(i!=j){Sum+=Calc(i,j);if(Sum>K)break;}
		Ans=min(Ans,Sum);
	}
}
int main(){
//	freopen("table.in","r",stdin);
//	freopen("table.out","w",stdout);
	n=read();m=read();K=read();Ans=K+1;int sum=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){a[i][j]=read();sum+=a[i][j];}
	Ans=min(Ans,min(sum,n*m-sum));
	Solve();Reverse();Solve();
	printf("%d\n",(Ans<=K?Ans:-1));
	return 0;
}
