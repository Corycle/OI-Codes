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
const int N=250;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,maxx,total;
int dis[N][N],g[N][N],p[N][N],vis[N],pnum[N];
void Build(int mx){
	for(int i=n+1;i<=total;i++){
		for(int j=1;j<=n;j++){
			if(dis[i][j]<=mx)g[i][j]=1;
			else g[i][j]=0;
		}
	}
}
bool DFS(int x){
	for(int y=1;y<=n;y++){
		if(g[x][y]&&!vis[y]){
			vis[y]=1;
			if(pnum[y]<maxx){
				p[y][++pnum[y]]=x;
				return true;
			}
			for(int i=1;i<=pnum[y];i++){
				if(DFS(p[y][i])){
					p[y][i]=x;
					return true;
				}
			}
		}
	}
	return false;
}
bool Hungary(){
	memset(p,0,sizeof(p));
	memset(pnum,0,sizeof(pnum));
	for(int i=n+1;i<=total;i++){
		memset(vis,0,sizeof(vis));
		if(!DFS(i))return false;
	}
	return true;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();maxx=read();
	total=n+m;
	for(int i=1;i<=total;i++){
		for(int j=1;j<=total;j++){
			dis[i][j]=read();
			if(dis[i][j]==0)dis[i][j]=inf;
		}
	}
	for(int k=1;k<=total;k++){
		for(int i=1;i<=total;i++){
			for(int j=1;j<=total;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	int l=0,r=inf/2,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		Build(mid);
		if(Hungary()){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
}
