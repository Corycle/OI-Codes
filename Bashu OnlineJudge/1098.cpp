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
int n,m,h[50005],cnt,r[10],fa[50005],dis[50005],vis[50005],ans=0x3f3f3f3f,a[10][10];
struct edge{
	int to,next,data;
}d[200005];
void hqq_add(int x,int y,int z){
	cnt++;
	d[cnt].data=z;
	d[cnt].next=h[x];
	d[cnt].to=y;
	h[x]=cnt;
}
queue<int>q;
bool cmd(int x,int y){
	return dis[x]>dis[y];
}
void spfa(int s){
	int i,j,k;
	memset(dis,0x3f,sizeof(dis));
	q.push(r[s]);
	dis[r[s]]=0;vis[r[s]]=1;
	while(q.size()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>dis[x]+d[i].data){
				dis[y]=dis[x]+d[i].data;
				fa[y]=x;
				if(vis[y]==0){
					q.push(y);
					vis[y]=1;
				}
			}
		}
	}
	for(i=0;i<=5;i++)a[s][i]=dis[r[i]];
}
void dfs(int fx,int x,int num){
	int i,j,k;
	if(x==6){
		ans=min(ans,num);
		return;
	}
	for(i=1;i<=5;i++){
		if(vis[i]==0){
			vis[i]=1;
			dfs(i,x+1,num+a[fx][i]);
			vis[i]=0;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=5;i++)r[i]=read();
	for(i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		hqq_add(x,y,z);
		hqq_add(y,x,z);
	}
	r[0]=1;
	for(i=0;i<=5;i++)spfa(i);
	memset(vis,0,sizeof(vis));
	vis[0]=1;
	dfs(0,1,0);
	printf("%d",ans);
	return 0;
}