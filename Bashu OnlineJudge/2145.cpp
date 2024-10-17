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
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p[150][150],ans;
int dx[5]={0,1,0,-1,0};//↓→↑← 
int dy[5]={0,0,1,0,-1};
void dfs(int x,int y,int f,int sum){
	int i,j,k;
	ans=max(ans,sum);
	p[x][y]=1;
	int fx=x+dx[f],fy=y+dy[f];
	if(p[fx][fy]==0)dfs(fx,fy,f,sum+1);
	if(p[fx][fy]==1){
		p[x][y]=0;
		return;
	}
	if(p[fx][fy]==-1){
		for(i=1;i<=4;i++){
			fx=x+dx[i];
			fy=y+dy[i];
			if(p[fx][fy]==0)dfs(fx,fy,i,sum+1);
		}
	}
	p[x][y]=0;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=m=read();
	int T=read();
	memset(p,-1,sizeof(p));
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			p[i][j]=0;
		}
	}
	while(T--){
		char y;
		cin>>y;
		int x=read();
		p[x][y-'A'+1]=-1;
	}
	dfs(1,1,1,1);
	dfs(1,1,2,1);
	printf("%d",ans);
	return 0;
}