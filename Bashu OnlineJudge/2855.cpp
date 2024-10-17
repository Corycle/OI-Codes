#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-5;
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
double f[N][N],val[N];
int fa[N],sum[N],h[N];
int v1[N],v2[N],vis[N];
struct edge{int to,next;}d[N*N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(int x){
	sum[x]=1;
	f[x][0]=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y);
		sum[x]+=sum[y];
		for(int j=min(m,sum[x]);j>=0;j--){
			for(int k=1;k<=j;k++){
				f[x][j]=max(f[x][j],f[x][j-k]+f[y][k]);
			}
		}
	}
	for(int i=m;i>=1;i--){
		f[x][i]=f[x][i-1]+val[x];
	}
}
bool Check(double x){
	for(int i=1;i<=n;i++){
		fa[i]=0;
		val[i]=(double)v1[i]-x*v2[i];
		for(int j=0;j<=m;j++){
			f[i][j]=-inf;
		}
	}
	DFS(1);
	for(int i=1;i<=n;i++){
		if(f[i][m]>=0)return true;
	}
	return false;
}
int main(){
//	freopen("plan.in","r",stdin);
//	freopen("plan.out","w",stdout);
	n=read();m=n-read();
	for(int i=1;i<=n;i++)v1[i]=read();
	for(int i=1;i<=n;i++)v2[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	double l=0,r=1e6,ans=0;
	while(r-l>eps){
		double mid=(l+r)/2;
		if(Check(mid)){
			ans=mid;
			l=mid;
		}
		else r=mid;
	}
	printf("%.1lf",ans);
	return 0;
}
/*
5 2
1 4 2 3 3
1 5 4 2 7
1 2
2 3
1 4
1 5

*/