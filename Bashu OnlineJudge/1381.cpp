#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
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
char a[N][N];
int dis[N][N],vis[N][N];
int dis1[N][N],dis2[N][N];
struct Node{int x,y;};
bool operator<(Node A,Node B){
	return dis[A.x][A.y]>dis[B.x][B.y];
}
void SPFA(int fx,int fy){
	priority_queue<Node>q;q.push((Node){fx,fy});
	memset(dis,0x3f,sizeof(dis));dis[fx][fy]=0;
	while(q.size()){
		int sx=q.top().x,tx;
		int sy=q.top().y,ty;
		vis[sx][sy]=0;q.pop();
		tx=sx+1;ty=sy+1;
		if(1<=tx&&tx<=n+1&&1<=ty&&ty<=m+1){
			int Dist=dis[sx][sy];if(a[sx][sy]=='/')Dist++;
			if(dis[tx][ty]>Dist){
				dis[tx][ty]=Dist;
				if(!vis[tx][ty]){
					vis[tx][ty]=1;
					q.push((Node){tx,ty});
				}
			}
		}
		tx=sx+1;ty=sy-1;
		if(1<=tx&&tx<=n+1&&1<=ty&&ty<=m+1){
			int Dist=dis[sx][sy];if(a[sx][ty]!='/')Dist++;
			if(dis[tx][ty]>Dist){
				dis[tx][ty]=Dist;
				if(!vis[tx][ty]){
					vis[tx][ty]=1;
					q.push((Node){tx,ty});
				}
			}
		}
		tx=sx-1;ty=sy+1;
		if(1<=tx&&tx<=n+1&&1<=ty&&ty<=m+1){
			int Dist=dis[sx][sy];if(a[tx][sy]!='/')Dist++;
			if(dis[tx][ty]>Dist){
				dis[tx][ty]=Dist;
				if(!vis[tx][ty]){
					vis[tx][ty]=1;
					q.push((Node){tx,ty});
				}
			}
		}
		tx=sx-1;ty=sy-1;
		if(1<=tx&&tx<=n+1&&1<=ty&&ty<=m+1){
			int Dist=dis[sx][sy];if(a[tx][ty]=='/')Dist++;
			if(dis[tx][ty]>Dist){
				dis[tx][ty]=Dist;
				if(!vis[tx][ty]){
					vis[tx][ty]=1;
					q.push((Node){tx,ty});
				}
			}
		}
	}
//	cout<<"====================="<<endl;
//	cout<<fx<<" "<<fy<<endl;
//	for(int i=1;i<=n+1;i++){
//		for(int j=1;j<=m+1;j++){
//			printf("%12d",dis[i][j]);
//		}
//		cout<<endl;
//	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();m=read();
		for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
		SPFA(1,1);memcpy(dis1,dis,sizeof(dis1));
		SPFA(n+1,m+1);memcpy(dis2,dis,sizeof(dis2));
		int ans=inf;
		for(int i=1;i<=n+1;i++){
			for(int j=1;j<=m+1;j++){
				ans=min(ans,dis1[i][j]+dis2[i][j]);
			}
		}
		if(ans==inf)printf("NO SOLUTION\n");
		else printf("%d\n",ans);
	}
	return 0;
}