#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,b,cnt,ans,root;
int h[N],a[N],vis[N],f[N][2];
struct edge{
	int to,next;
}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int dfs(int x){
	vis[x]=1;
	if(vis[a[x]])return x;
	return dfs(a[x]);
}
void DFS(int x,int fa){
	vis[x]=1;
	f[x][1]=1;
	f[x][0]=inf;
	if(x==b)f[x][0]=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y!=root){
			DFS(y,x);
			f[x][0]+=min(f[y][1],f[y][0]);
			f[x][0]=min(f[x][0],f[x][1]+f[y][1]-1);
			f[x][1]+=min(f[y][0],f[y][1]);
		}
	}
}
/*
	由于是基环树林 
	所以我们选择一个环上的点 
	拆掉它的出边 设这个点为root 出边指向的点为b
*/
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		Add(a[i],i);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			root=dfs(i);
			b=a[root];DFS(root,0);
			int tmp=f[root][1];
			b=0;DFS(root,0);
			ans+=min(tmp,f[root][0]);
		}
	}
	printf("%d",n-ans);
	return 0;
}