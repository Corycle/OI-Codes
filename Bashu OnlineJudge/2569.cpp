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
const int N=4005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int g[N][N],vis[N],p[N];
int DFS(int x){
	for(int y=1;y<=n;y++){
		if(g[x][y]&&!vis[y]){
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
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		if(DFS(i))tmp++;
	}
	return tmp;
}
void Print(int x){
	if(!x)return;
	Print(p[x]);
	printf("%d ",x);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		g[x][y]=1;
	}
	int ans=n-Hungary();
	printf("%d\n",ans);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)vis[p[i]]=1;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			Print(i);
			printf("0\n");
		}
	}
	return 0;
}