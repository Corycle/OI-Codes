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
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
const int inf=0x3f3f3f3f;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,dis[1005],vis[1005],c[1005],a[1005][1005],q[10005];
int spfa(int s){
	int i,j,k;
	memset(dis,0x3f,sizeof(dis));
	int h=1,t=1;
	q[1]=s;vis[s]=1;dis[s]=0;
	while(h<=t){
		int x=q[h++];
		vis[x]=0;
		for(i=1;i<=n;i++){
			if(a[x][i]==inf)continue;
			int y=i;
			if(dis[y]>dis[x]+a[x][y]){
				c[y]++;
				if(c[y]==n+2)return 0;
				dis[y]=dis[x]+a[x][y];
				if(vis[y]==0){
					vis[y]=1;
					q[++t]=y;
				}
			}
		}
	}
	return 1;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	memset(a,0x3f,sizeof(a));
	n=read();m=read();
	int s=read();
	for(i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		a[x][y]=min(a[x][y],z);
	}
	if(spfa(s)){
		for(i=1;i<=n;i++){
			if(dis[i]!=inf)printf("%d\n",dis[i]);
			else printf("NoPath\n");
		}
	}
	else printf("-1");
	return 0;
}