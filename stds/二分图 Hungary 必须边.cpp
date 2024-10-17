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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt;
int g[N][N],p[N],vis[N],ans[N],b[N];
bool DFS(int x){
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
	memset(p,0,sizeof(p));
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		if(DFS(i))tmp++;
	}
	return tmp;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			g[i][j]=1;
		}
	}
	while(1){
		int x=read(),y=read();
		if(!x&&!y)break;
		g[x][y]=0;
	}
	cnt=Hungary();
//	if(cnt!=n){
//		printf("none");
//		return 0;
//	}
	memcpy(b,p,sizeof(b));
	for(int i=1;i<=n;i++){
		g[b[i]][i]=0;
		int sum=Hungary();
		if(sum!=cnt)ans[b[i]]=i;
		g[b[i]][i]=1;
	}
	int num=0;
	for(int i=1;i<=n;i++){
		if(ans[i]){
			num++;
			printf("%d %d\n",i,ans[i]);
		}
	}
	if(!num)printf("none");
	return 0;
}
