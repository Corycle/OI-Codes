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
const int N=505;
const int M=255;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
	0 1 
	3 2 
*/
char s[N][N];
int n,m,Q,Max,f[N][N],g[4][N][N],sum[M][N][N];
bool Check(int t,int x,int y,int k){
	if(s[x][y]!=s[x+1][y]||s[x][y]!=s[x][y+1]||s[x][y]!=s[x+1][y+1])return false;
	if(g[t][x][y]<k||g[t][x+1][y]<k||g[t][x][y+1]<k||g[t][x+1][y+1]<k)return false;
	return true;
}
int Count(int t,int l1,int r1,int l2,int r2){
	return sum[t][l2][r2]+sum[t][l1-1][r1-1]-sum[t][l1-1][r2]-sum[t][l2][r1-1];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();Max=min(n,m)/2;
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)for(int k=0;k<4;k++)g[k][i][j]=1;
	for(int k=2;k<=Max;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(Check(0,i-1,j-1,k-1))g[0][i][j]=k;
				if(Check(1,i-1,j,k-1))g[1][i][j]=k;
				if(Check(2,i,j,k-1))g[2][i][j]=k;
				if(Check(3,i,j-1,k-1))g[3][i][j]=k;
			}
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			if(s[i][j]!='R'||s[i][j+1]!='G'||s[i+1][j+1]!='B'||s[i+1][j]!='Y')continue;
			f[i][j]=min(min(g[0][i][j],g[1][i][j+1]),min(g[2][i+1][j+1],g[3][i+1][j]));
		}
	}
//	for(int i=1;i<=n;i++){for(int j=1;j<=m;j++)cout<<f[i][j]<<" ";cout<<endl;}cout<<endl;
//	for(int i=1;i<=n;i++){for(int j=1;j<=m;j++)cout<<g[0][i][j]<<" ";cout<<endl;}cout<<endl;
//	for(int i=1;i<=n;i++){for(int j=1;j<=m;j++)cout<<g[1][i][j]<<" ";cout<<endl;}cout<<endl;
//	for(int i=1;i<=n;i++){for(int j=1;j<=m;j++)cout<<g[2][i][j]<<" ";cout<<endl;}cout<<endl;
//	for(int i=1;i<=n;i++){for(int j=1;j<=m;j++)cout<<g[3][i][j]<<" ";cout<<endl;}cout<<endl;
	for(int k=1;k<=Max;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				sum[k][i][j]=sum[k][i-1][j]+sum[k][i][j-1]-sum[k][i-1][j-1]+(f[i][j]>=k);
			}
		}
	}
	while(Q--){
		int l1=read(),r1=read(),l2=read(),r2=read();
		int l=1,r=min(l2-l1+1,r2-r1+1)/2,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(Count(mid,l1+mid-1,r1+mid-1,l2-mid,r2-mid)){ans=mid;l=mid+1;}
			else r=mid-1;
		}
		printf("%d\n",ans*ans*4);
	}
	return 0;
}
