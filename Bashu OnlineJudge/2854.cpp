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
const int M=35000;
const int N=105;
inline int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,ans=inf;
int a[N],usd[N],vis[N];
int f[N][M],d[N][N];
inline void DFS(int x,int tot,int depth){
	if(tot>=ans)return;
	if(tot>=f[x][depth])return;
	f[x][depth]=tot;
	if(depth==(1<<p)-1){
		ans=min(ans,tot+d[x][1]);
		return;
	}
	for(int i=1;i<=p;i++){
		int y=usd[i];
		if(!vis[y]&&d[x][y]!=inf){
			vis[y]=1;
			DFS(y,tot+d[x][y],depth|(1<<(i-1)));
			vis[y]=0;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	memset(f,0x3f,sizeof(f));
	memset(d,0x3f,sizeof(d));
	n=read();p=read();m=read();
	for(int i=1;i<=p;i++){
		usd[i]=read();
		if(usd[i]==1){
			p--;i--;
		}
	}
	for(int i=1;i<=n;i++)d[i][i]=0;
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		d[x][y]=d[y][x]=min(d[x][y],z);
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(d[i][k]!=inf&&d[k][j]!=inf){
					d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
				}
			}
		}
	}
	sort(usd+1,usd+p+1);
	DFS(1,0,0);
	printf("%d",ans);
	return 0;
}