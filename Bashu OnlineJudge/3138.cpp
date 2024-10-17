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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,h[1005],cnt,ans=0x3f3f3f3f,dis[1005][1005],vis[1005];
struct edge{
	int to,next,data;
}d[10005];
void hqq_add(int x,int y,int z){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	d[cnt].data=z;
	h[x]=cnt;
}
queue<int>q;
void spfa(int s){
	int i,j,k;
	memset(vis,0,sizeof(vis));
	for(i=1;i<=n;i++)dis[s][i]=0x3f3f3f3f;
	dis[s][s]=0;
	vis[s]=1;
	while(q.size())q.pop();
	q.push(s);
	while(q.size()){
		int x=q.front();
		q.pop();
		for(i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[s][y]>dis[s][x]+d[i].data){
				dis[s][y]=dis[s][x]+d[i].data;
				if(vis[y]==0){
					vis[y]=1;
					q.push(y);
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
	while(m--){
		i=read();j=read();k=read();
		hqq_add(i,j,k);
	}
	for(i=1;i<=n;i++)spfa(i);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(i!=j)ans=min(ans,dis[i][j]+dis[j][i]);
		}
	}
	printf("%d",ans);
	return 0;
}