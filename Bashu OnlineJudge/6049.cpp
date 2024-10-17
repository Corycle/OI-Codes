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
const int N=305;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll f[N][N][2];
int n,m,sum[N],g[N][N];
struct Node{ll k;int x;}P[N];
bool cmp(Node A,Node B){return A.k<B.k;}
ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
ll Sum(int l,int r){return sum[r]-sum[l-1];}
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){P[i].k=read();P[i].x=read();}
	sort(P+1,P+n+1,cmp);
	memset(f,-0x3f,sizeof(f));
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+P[i].x;
	for(int i=1;i<=n;i++)f[i][i][0]=f[i][i][1]=P[i].x;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j)g[i][j]=(gcd(P[i].k,P[j].k)!=1);
	for(int t=2;t<=n;t++){
		for(int i=1;i+t-1<=n;i++){
			int j=i+t-1;
			for(int k=i;k<=j;k++){
				if(k!=j&&g[j][k])f[i][j][1]=max(f[i][j][1],f[i][k][1]+f[k][j-1][0]-P[k].x+Sum(i,j));
				if(k!=i&&g[i][k])f[i][j][0]=max(f[i][j][0],f[i+1][k][1]+f[k][j][0]-P[k].x+Sum(i,j));
			}
		}
	}
	ll Ans=-inf;
	for(int i=1;i<=n;i++)Ans=max(Ans,f[1][i][1]+f[i][n][0]-P[i].x);
	printf("%lld\n",Ans>=0?Ans:-1);
	return 0;
}