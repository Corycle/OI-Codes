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
int n,m,a[1005][1005],t[1005][1005],dis[1005][1005],ans;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
queue<int>q1,q2;
void bfs1(){
	int i,j,k;
	while(q1.size()){
		int x=q1.front(),y=q2.front();
		q1.pop();q2.pop();
		for(i=0;i<4;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(fx<1||fy<1||fx>n||fy>m)continue;
			if(t[fx][fy]||a[fx][fy]==1)continue;
			t[fx][fy]=t[x][y]+1;
			q1.push(fx);q2.push(fy);
		}
	}
}
void bfs2(int xx,int yy){
	int i,j,k;
	while(q1.size()){q1.pop();q2.pop();}
	memset(dis,0,sizeof(dis));
	q1.push(xx);q2.push(yy);
	while(q1.size()){
		int x=q1.front(),y=q2.front();
		q1.pop();q2.pop();
		for(i=0;i<4;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(fx<1||fy<1||fx>n||fy>m)continue;
			if(dis[fx][fy]||fx==xx&&fy==yy)continue;
			dis[fx][fy]=dis[x][y]+1;
			if(dis[fx][fy]>=t[fx][fy])continue;
			if(a[fx][fy]==3){
				ans++;
				return;
			}
			q1.push(fx);q2.push(fy);
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
			if(a[i][j]==1){
				q1.push(i);
				q2.push(j);
			}
		}
	}
	bfs1();
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(a[i][j]==2){
				bfs2(i,j);
			}
		}
	}
	printf("%d",ans);
	return 0;
}