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
const int N=1005;
const int M=45;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
vector<int>Gx[M],Gy[M];
int n,m,K,Q,a[N][N],b[N],vis[N][N],dis[M][N][N];
void Update(int c,int dis[][N]){
	queue<int>qx,qy;
	for(int i=1;i<=K;i++)b[i]=0;b[c]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			vis[i][j]=0;
			if(a[i][j]==c){vis[i][j]=1;dis[i][j]=0;qx.push(i);qy.push(j);}
		}
	}
	while(qx.size()){
		int x=qx.front(),y=qy.front();qx.pop();qy.pop();
		if(!b[a[x][y]]){
			b[a[x][y]]=1;
			int num=Gx[a[x][y]].size();
			for(int i=0;i<num;i++){
				int fx=Gx[a[x][y]][i],fy=Gy[a[x][y]][i];
				if(fx<1||fx>n||fy<1||fy>m||vis[fx][fy])continue;
				vis[fx][fy]=1;dis[fx][fy]=dis[x][y]+1;qx.push(fx);qy.push(fy);
			}
		}
		for(int i=0;i<4;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(fx<1||fx>n||fy<1||fy>m||vis[fx][fy])continue;
			vis[fx][fy]=1;dis[fx][fy]=dis[x][y]+1;qx.push(fx);qy.push(fy);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			Gx[a[i][j]].push_back(i);
			Gy[a[i][j]].push_back(j);
		}
	}
	for(int c=1;c<=K;c++)Update(c,dis[c]);
	Q=read();
	while(Q--){
		int sx=read(),sy=read(),tx=read(),ty=read(),ans=inf;
		for(int c=1;c<=K;c++)ans=min(ans,dis[c][sx][sy]+dis[c][tx][ty]+1);
		printf("%d\n",min(ans,abs(sx-tx)+abs(sy-ty)));
	}
	return 0;
}
