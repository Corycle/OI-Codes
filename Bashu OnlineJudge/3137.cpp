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
int n,m,a[1005][1005],dis[1005][1005],vis[1005][1005],ans=inf;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
struct node{
	int x,y;
};
bool operator<(node x,node y){
	return dis[x.x][x.y]>dis[y.x][y.y];
}
priority_queue<node>q;
void ask(){
	int i,j,k;
	for(i=1;i<=m;i++){
		q.push((node){1,i});
		dis[1][i]=0;
		vis[1][i]=1;
	}
	while(q.size()){
		int x=q.top().x,y=q.top().y;
		q.pop();
		vis[x][y]=0;
		for(i=0;i<4;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(max(dis[x][y],a[fx][fy])<dis[fx][fy]){
				dis[fx][fy]=max(dis[x][y],a[fx][fy]);
				if(!vis[fx][fy]){
					vis[fx][fy]=1;
					q.push((node){fx,fy});
				}
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			a[i][j]=read();
			dis[i][j]=inf;
		}
	}
	ask();
	for(i=1;i<=m;i++)ans=min(ans,dis[n][i]);
	printf("%d",ans);
	return 0;
}