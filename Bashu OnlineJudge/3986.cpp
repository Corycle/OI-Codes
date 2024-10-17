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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K;
int a[N][N],b[N][N],l[N][N],r[N][N],u[N][N];
int Calc(int x){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)b[i][j]=(a[i][j]>=x);
		for(int j=1;j<=m;j++)l[i][j]=(b[i][j]?l[i][j-1]+1:0);
		for(int j=m;j>=1;j--)r[i][j]=(b[i][j]?r[i][j+1]+1:0);
		for(int j=1;j<=m;j++)u[i][j]=(b[i][j]?u[i-1][j]+1:0);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!b[i][j])continue;
			if(b[i-1][j]){
				l[i][j]=min(l[i][j],l[i-1][j]);
				r[i][j]=min(r[i][j],r[i-1][j]);
			}
			ans=max(ans,u[i][j]*(r[i][j]+l[i][j]-1));
		}
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)a[i][j]=read();
	}
	int l=1,r=1e9,ans=1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Calc(mid)>=K){
			ans=mid;l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d %d",ans,Calc(ans));
	return 0;
}