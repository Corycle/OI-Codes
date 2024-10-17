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
int n,m,A,B,C;
int a[N][N],dis[N][N][15],vis[N][N][15];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
struct node{int x,y,z;};
void SPFA(){
	queue<node>q;
	memset(dis,0x3f,sizeof(dis));
	q.push((node){1,1,m});
	dis[1][1][m]=0;
	while(q.size()){
		node x=q.front();
		q.pop();
		vis[x.x][x.y][x.z]=0;
		for(int i=0;i<4;i++){
			node y=(node){x.x+dx[i],x.y+dy[i],x.z-1};
			if(y.x>n||y.x<1||y.y>n||y.y<1)continue;
			int data=dis[x.x][x.y][x.z];
			if(a[y.x][y.y]==1){
				data+=A;
				y.z=m;
//				cout<<y.x<<" "<<y.y<<" "<<y.z<<" "<<data<<endl;
			}
			if(i==2||i==3)data+=B;
			if(y.z==0&&a[y.x][y.y]==0&&(y.x!=n||y.y!=n)){
				y.z=m;
				data+=A+C;
			}
			if(dis[y.x][y.y][y.z]>data){
				dis[y.x][y.y][y.z]=data;
				if(!vis[y.x][y.y][y.z]){
					q.push(y);
					vis[y.x][y.y][y.z]=1;
				}
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	A=read();B=read();C=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=read();
		}
	}
	SPFA();
	int ans=inf;
	for(int i=0;i<=m;i++){
//		if(dis[n][n][i]==0)cout<<i<<endl;
		ans=min(ans,dis[n][n][i]);
	}
	printf("%d",ans);
	return 0;
}