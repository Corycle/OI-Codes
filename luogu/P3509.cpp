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
const int N=1e6+5;
const int M=61;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll m,a[N];
int n,K,p[N][M];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1,l=1,r=K+1;i<=n;i++){
		while(r<n&&a[r+1]-a[i]<a[i]-a[l]){l++;r++;}
		p[i][0]=((a[i]-a[l]>=a[r]-a[i])?l:r);
	}
	for(int j=1;j<M;j++)for(int i=1;i<=n;i++)p[i][j]=p[p[i][j-1]][j-1];
	for(int i=1;i<=n;i++){
		int x=i;
		for(int j=M-1;j>=0;j--)if((m>>j)&1)x=p[x][j];
		printf("%d ",x);
	}
	printf("\n");
	return 0;
}
