#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
int read(){
	int s=0;int f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[2005][2005],dis[2005],vis[2005],num[2005];
int dijkstra(int s){
	int i,j,k;
	for(i=1;i<=n;i++){
		dis[i]=a[s][i];
		if(dis[i]!=0x3f3f3f3f)num[i]=1;
	}
	dis[s]=0;vis[s]=1;
	for(i=1;i<=n;i++){
		k=0;
		int l=0x3f3f3f3f;
		for(j=1;j<=n;j++){
			if(vis[j]==0&&l>dis[j]){
				k=j;l=dis[j];
			}
		}
		vis[k]=1;
		if(k==0)break;
		for(j=1;j<=n;j++){
			if(j==k)continue;
			if(a[k][j]==0x3f3f3f3f)continue;
			if(dis[k]+a[k][j]<dis[j]){
				dis[j]=dis[k]+a[k][j];
				num[j]=num[k];
			}
			else if(dis[k]+a[k][j]==dis[j]){
				num[j]+=num[k];
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	memset(a,0x3f,sizeof(a));
	for(i=1;i<=m;i++){
		j=read();k=read();
		a[j][k]=min(a[j][k],read());
	}
	for(i=1;i<=n;i++)a[i][i]=0;
	dijkstra(1);
	if(dis[n]!=0x3f3f3f3f)printf("%d %d",dis[n],num[n]);
	else printf("No answer");
	return 0;
}