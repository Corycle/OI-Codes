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
const int N=705;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
int c[N],w[N],a[N][N],sum[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=n;i++)w[i]=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		a[x][y]=1;
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]|=(a[i][k]&a[k][j]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(c[i]==1){
			for(int j=1;j<=n;j++)sum[j]=0;
			for(int j=1;j<=n;j++)if(a[i][j])sum[c[j]]+=w[j];
			for(int j=2;j<=n;j++)Ans=max(Ans,sum[j]/w[i]);
		}
	}
	printf("%d",Ans);
	return 0;
}