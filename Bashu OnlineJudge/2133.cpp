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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int g[N][N],p[N],vis[N];
bool Hungary(int x){
	for(int y=1;y<=m;y++){
		if(g[x][y]&&!vis[y]){
			vis[y]=1;
			if(!p[y]||Hungary(p[y])){
				p[y]=x;
				return true;
			}
		}
	}
	return false;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int num=read();
		for(int j=1;j<=num;j++){
			int x=read();
			g[i][x]=1;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		if(Hungary(i))ans++;
	}
	printf("%d",ans);
	return 0;
}