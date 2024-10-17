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
const int N=50;
const int M=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt1,cnt2;
int vis[M],p[M];
int a[N][N],g[M][M];
struct Answer{
	int x,y;
}ans1[M],ans2[M];
bool cmp(Answer x,Answer y){
	if(x.x!=y.x)return x.x<y.x;
	return x.y<y.y;
}
void Add(int sx,int sy,int tx,int ty){
	int x=(sx-1)*n+sy;
	int y=(tx-1)*n+ty;
	if(a[sx][sy]==1)swap(x,y);
	g[x][y]=1;
}
bool DFS(int x){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]==1){
				int y=(i-1)*n+j;
				if(g[x][y]&&!vis[y]){
					vis[y]=1;
					if(!p[y]||DFS(p[y])){
						p[y]=x;
						return true;
					}
				}
			}
		}
	}
	return false;
}
int Hungary(){
	int tmp=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]==0){
				memset(vis,0,sizeof(vis));
				if(DFS((i-1)*n+j))tmp++;
			}
		}
	}
	return tmp;
}
void Build(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]==-1)continue;
			if(a[i][j+1]!=-1)Add(i,j,i,j+1);
			if(a[i+1][j]!=-1)Add(i,j,i+1,j);
		}
	}
}
void Print(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]==1){
				int y=(i-1)*n+j;
				int x=p[y];
				if(x==y+n)ans1[++cnt1]=(Answer){i,j};
				if(x==y+1)ans2[++cnt2]=(Answer){i,j};
				if(y==x+n)ans1[++cnt1]=(Answer){i-1,j};
				if(y==x+1)ans2[++cnt2]=(Answer){i,j-1};
			}
		}
	}
	sort(ans1+1,ans1+cnt1+1,cmp);
	sort(ans2+1,ans2+cnt2+1,cmp);
	printf("%d\n",cnt1);
	for(int i=1;i<=cnt1;i++){
		printf("%d %d\n",ans1[i].x,ans1[i].y);
	}
	printf("%d\n",cnt2);
	for(int i=1;i<=cnt2;i++){
		printf("%d %d\n",ans2[i].x,ans2[i].y);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	memset(a,-1,sizeof(a));
	n=read();m=read();
	if((n*n-m)&1){
		printf("No");
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=(i+j)%2;
		}
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		a[x][y]=-1;
	}
	Build();
	int sum=Hungary();
	if(sum!=(n*n-m)/2){
		printf("No");
		return 0;
	}
	printf("Yes\n");
	Print();
	return 0;
}