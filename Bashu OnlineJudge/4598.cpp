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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int Lim=10000;
const int N=10005;
const int M=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
int a[N],f[N][M];
struct Tree{
	int c[M][N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y,int val){x++;for(int i=x;i<=m+1;i+=lowbit(i))for(int j=y;j<N;j+=lowbit(j))c[i][j]=max(c[i][j],val);}
	int Ask(int x,int y){int ans=0;x++;for(int i=x;i>=1;i-=lowbit(i))for(int j=y;j>=1;j-=lowbit(j))ans=max(ans,c[i][j]);return ans;}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++)f[i][j]=tree.Ask(j,a[i]+j)+1;
		for(int j=0;j<=m;j++)tree.Add(j,a[i]+j,f[i][j]);
		for(int j=0;j<=m;j++)Ans=max(Ans,f[i][j]);
	}
	printf("%d",Ans);
	return 0;
}