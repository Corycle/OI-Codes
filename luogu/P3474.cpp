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
ll sum[N][N];
int n,K,a[N][N],U[N][N],L[N][N],R[N][N];
ll Sum(int sx,int sy,int tx,int ty){return sum[tx][ty]+sum[sx-1][sy-1]-sum[tx][sy-1]-sum[sx-1][ty];}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	K=read();n=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[j][i]=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+a[i][j];
			if(K<=a[i][j]&&a[i][j]<=K*2){printf("%d %d %d %d\n",i,j,i,j);return 0;}
		}
	}
	int l=0,r=0,u=0,d=0,flag=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)U[i][j]=(a[i][j]<K?U[i-1][j]+1:0);
		for(int j=1;j<=n;j++)L[i][j]=(a[i][j]<K?L[i][j-1]+1:0);
		for(int j=n;j>=1;j--)R[i][j]=(a[i][j]<K?R[i][j+1]+1:0);
		for(int j=1;j<=n;j++)if(i!=1&&a[i-1][j]<K)L[i][j]=min(L[i][j],L[i-1][j]);
		for(int j=1;j<=n;j++)if(i!=1&&a[i-1][j]<K)R[i][j]=min(R[i][j],R[i-1][j]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]<K&&Sum(i-U[i][j]+1,j-L[i][j]+1,i,j+R[i][j]-1)>=K){
				l=j-L[i][j]+1;r=j+R[i][j]-1;u=i-U[i][j]+1;d=i;flag=1;break;
			}
		}
		if(flag)break;
	}
	if(!flag){puts("NIE");return 0;}
	while(u<=d){
		if(Sum(u,l,d,r)>=K&&Sum(u,l,d,r)<=K*2){printf("%d %d %d %d\n",u,l,d,r);return 0;}
		if(Sum(d,l,d,r)>=K){
			u=d;
			while(l<=r){
				if(Sum(u,l,d,r)>=K&&Sum(u,l,d,r)<=K*2){printf("%d %d %d %d\n",u,l,d,r);return 0;}
				r--;
			}
		}
		d--;
	}
	puts("NIE");
	return 0;
}
