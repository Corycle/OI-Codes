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
const int N=10005;
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[M][M];
int n,m,cnt,Ans,p[N],vis[N];
vector<int>G[N];
inline int id(int x,int y){return (x-1)*m+y;}
void Add(int x,int y){
	G[x].push_back(y);
	G[y].push_back(x);
}
bool Hungary(int x){
	for(auto y:G[x]){
		if(vis[y]==cnt)continue;
		vis[y]=cnt;
		if(!p[y]||Hungary(p[y])){
			p[x]=y;p[y]=x;
			return true;
		}
	}
	return false;
}
void DFS(int x){
	vis[x]=1;
	for(auto y:G[x]){
		if(!vis[p[y]])DFS(p[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='.'){
				if(i<n&&a[i+1][j]=='.')Add(id(i,j),id(i+1,j));
				if(j<m&&a[i][j+1]=='.')Add(id(i,j),id(i,j+1));
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='#')continue;
			if((i+j)&1){cnt++;Hungary(id(i,j));}
		}
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='#')continue;
			if(!p[id(i,j)]&&!vis[id(i,j)])DFS(id(i,j));
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			Ans+=vis[id(i,j)];
		}
	}
	printf("%d\n",Ans);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(vis[id(i,j)])printf("%d %d\n",i,j);
		}
	}
	return 0;
}