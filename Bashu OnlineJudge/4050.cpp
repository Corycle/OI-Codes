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
const int N=20;
const int M=1<<11;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,Sta,tot,cnt;
int ans,ansx,ansy,usd[N][N];
int dp[N][N][M],vis[N][N][M];
int val[N][N],sta[N][N],id[N][N];
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
struct node{
	int x,y,k;
}From[N][N][M];
queue<node>q;
void SPFA(){
	while(q.size()){
		node fx=q.front();q.pop();
		vis[fx.x][fx.y][fx.k]=0;
		for(int i=0;i<4;i++){
			int x=fx.x+dx[i];
			int y=fx.y+dy[i];
			int S=fx.k|sta[x][y];
			if(x<1||y<1||x>n||y>m)continue;
			if(dp[x][y][S]>dp[fx.x][fx.y][fx.k]+val[x][y]){
				dp[x][y][S]=dp[fx.x][fx.y][fx.k]+val[x][y];
				From[x][y][S]=fx;
				if(S==fx.k&&!vis[x][y][S]){
					q.push((node){x,y,S});
					vis[x][y][S]=1;
				}
			}
		}
	}
}
void Steiner_Tree(){
	for(int i=0;i<Sta;i++){
		for(int x=1;x<=n;x++)
		for(int y=1;y<=m;y++){
			int T=sta[x][y];
			if(!(i&T)&&T)continue;
			for(int k=i;k;k=(k-1)&i){
				int dlt=dp[x][y][k]+dp[x][y][(i-k)];
				if(dp[x][y][i]>dlt-val[x][y]){
					dp[x][y][i]=dlt-val[x][y];
					From[x][y][i].x=x;
					From[x][y][i].y=y;
					From[x][y][i].k=k;
				}
			}
			if(dp[x][y][i]!=inf){
				vis[x][y][i]=1;
				q.push((node){x,y,i});
			}
		}
		SPFA();
	}
}
void DFS(int x,int y,int k){
	if(From[x][y][k].k==0)return;
	usd[x][y]=1;
	if(x!=From[x][y][k].x||y!=From[x][y][k].y){
		DFS(From[x][y][k].x,From[x][y][k].y,From[x][y][k].k);
	}
	else{
		DFS(From[x][y][k].x,From[x][y][k].y,From[x][y][k].k);
		DFS(From[x][y][k].x,From[x][y][k].y,k-From[x][y][k].k);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	memset(dp,0x3f,sizeof(dp));
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			val[i][j]=read();
			if(!val[i][j]){
				sta[i][j]=1<<tot;tot++;
				dp[i][j][sta[i][j]]=0;
			}
		}
	}
	ans=inf;
	Sta=1<<tot;
	Steiner_Tree();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(ans>dp[i][j][Sta-1]){
				ans=dp[i][j][Sta-1];
				ansx=i;ansy=j;
			}
		}
	}
	printf("%d\n",ans);
	DFS(ansx,ansy,Sta-1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!val[i][j])printf("x");
			else if(usd[i][j])printf("o");
			else printf("_");
		}
		printf("\n");
	}
	return 0;
}