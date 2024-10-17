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
const int maxn=5001;
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
int a[N][N],sum[N][N];
int Sum(int sx,int sy,int tx,int ty){
	return sum[tx][ty]-sum[tx][sy-1]-sum[sx-1][ty]+sum[sx-1][sy-1];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		a[x+1][y+1]=read();
	}
	for(int i=1;i<=maxn;i++){
		for(int j=1;j<=maxn;j++){
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
		}
	}
	for(int i=1;i+m-1<=maxn;i++){
		for(int j=1;j+m-1<=maxn;j++){
			Ans=max(Ans,Sum(i,j,i+m-1,j+m-1));
		}
	}
	printf("%d",Ans);
	return 0;
}