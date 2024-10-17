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
int n,K,cnt;
ll f[N][N],g[N][N];
int h[N],fa[N],sum[N];
struct edge{int to,next;ll dist;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void DFS(int x){
	sum[x]=1;g[x][0]=g[x][1]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y);sum[x]+=sum[y];
		for(int j=min(sum[x],K);j>=0;j--){
			for(int k=0;k<=min(sum[y],j);k++){
				if(g[x][j-k]&&g[y][k]){
					ll val=d[i].dist*(k*(K-k)+(sum[y]-k)*(n-K-sum[y]+k));
					f[x][j]=max(f[x][j],f[x][j-k]+f[y][k]+val);
					g[x][j]=1;
				}
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	DFS(1);
	printf("%lld",f[1][K]);
	return 0;
}