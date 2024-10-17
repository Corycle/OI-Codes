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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int p[N],g[N][N],b[N],vis[N],ans[N];
struct node{
	int xmin,xmax,ymin,ymax;
}s[N];
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
	int T=0;
	while(1){
		n=read();
		if(!n)break;
		memset(g,0,sizeof(g));
		memset(ans,0,sizeof(ans));
		for(int i=1;i<=n;i++){
			s[i].xmin=read();s[i].xmax=read();
			s[i].ymin=read();s[i].ymax=read();
		}
		for(int i=1;i<=n;i++){
			int x=read(),y=read();
			for(int j=1;j<=n;j++){
				if(s[j].xmin<x&&x<s[j].xmax&&s[j].ymin<y&&y<s[j].ymax)g[i][j]=1;
			}
		}
		int cnt=Hungary();
		memcpy(b,p,sizeof(b));
		for(int i=1;i<=n;i++){
			g[b[i]][i]=0;
			int sum=Hungary();
			if(sum!=cnt)ans[i]=b[i];
			g[b[i]][i]=1;
		}
		printf("Heap %d\n",++T);
		int flag=0;
		for(int i=1;i<=n;i++){
			if(ans[i]){
				printf("(%c,%d) ",(char)(i+'A'-1),ans[i]);
				flag=1;
			}
		}
		if(!flag)printf("none");
		printf("\n\n");
	}
	return 0;
}