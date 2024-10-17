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
const int N=205;
const int M=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,cnt1,cnt2;
int a[N][N],p1[N][N],p2[N][N];
int p[M],vis[M],h[M];
struct edge{
	int to,next;
}d[M*50];
void edge_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
bool DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!vis[y]){
			vis[y]=1;
			if(!p[y]||DFS(p[y])){
				p[y]=x;
				return true;
			}
		}
	}
	return false;
}
int Hungary(){
	int tmp=0;
	for(int i=1;i<=cnt1;i++){
		memset(vis,0,sizeof(vis));
		if(DFS(i))tmp++;
	}
	return tmp;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	memset(a,-1,sizeof(a));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			if(a[i][j]==2)a[i][j]=-1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==-1)continue;
			if(a[i][j-1]!=-1)p1[i][j]=cnt1;
			else p1[i][j]=++cnt1;
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			if(a[i][j]==-1)continue;
			if(a[i-1][j]!=-1)p2[i][j]=cnt2;
			else p2[i][j]=++cnt2;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==0)edge_add(p1[i][j],p2[i][j]);
		}
	}
	int ans=Hungary();
	printf("%d",ans);
	return 0;
}