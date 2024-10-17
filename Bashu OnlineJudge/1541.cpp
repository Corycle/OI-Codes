/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
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
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int n,m,a[N][N],f[N][N][3],vis[N][N][3];
struct Node{
	int x,y,t,dis;
	friend bool operator<(Node A,Node B){return A.dis>B.dis;}
};
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=read();
	priority_queue<Node>q;q.push((Node){1,1,0,0});
	memset(f,0x3f,sizeof(f));f[1][1][0]=0;
	while(q.size()){
		Node A=q.top();q.pop();
		if(vis[A.x][A.y][A.t])continue;vis[A.x][A.y][A.t]=1;
		for(int i=0;i<4;i++){
			int x=A.x+dx[i],y=A.y+dy[i],t=(A.t+1)%3;
			if(x<1||x>n||y<1||y>n)continue;
			if(f[x][y][t]>A.dis+m+(t==0)*a[x][y]){
				f[x][y][t]=A.dis+m+(t==0)*a[x][y];
				q.push((Node){x,y,t,f[x][y][t]});
			}
		}
	}
	printf("%d\n",min(min(f[n][n][0],f[n][n][1]),f[n][n][2]));
	return 0;
}
