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
const int N=1e5+5;
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N];
vector<int>G[N];
ll Ans,sum[N],f[N][M],g[N][M];
void Prepare(int x,int fa){
	for(int i=1;i<=m;i++){f[x][i]=sum[x];g[x][i]=sum[x]-a[fa];}
}
void Update(int x,int y,int fa){
	for(int i=0;i<=m;i++)Ans=max(Ans,f[x][i]+g[y][m-i]);
	for(int i=1;i<=m;i++){
		f[x][i]=max(f[x][i],max(f[y][i],f[y][i-1]+sum[x]-a[y]));
		g[x][i]=max(g[x][i],max(g[y][i],g[y][i-1]+sum[x]-a[fa]));
	}
}
void DFS(int x,int fa){
	int num=G[x].size()-1;
	for(int i=0;i<=num;i++){int y=G[x][i];if(y!=fa)DFS(y,x);}
	Prepare(x,fa);for(int i=0;i<=num;i++){int y=G[x][i];if(y!=fa)Update(x,y,fa);}
	Prepare(x,fa);for(int i=num;i>=0;i--){int y=G[x][i];if(y!=fa)Update(x,y,fa);}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);sum[x]+=a[y];sum[y]+=a[x];}
	DFS(1,0);
	printf("%lld\n",Ans);
	return 0;
}
