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
int n,m,h[40005],cnt,head[40005],qnt,g[40005],vis[40005],mark[40005],ans[40005],dis[40005];
struct edge{
	int to,data,next;
}d[80005];
struct question{
	int to,next,num;
}q[80005];
void hqq_add(int x,int y,int z){
	cnt++;
	d[cnt].data=z;
	d[cnt].next=h[x];
	d[cnt].to=y;
	h[x]=cnt;
}
void hqq_add2(int x,int y,int z){
	qnt++;
	q[qnt].to=y;
	q[qnt].next=head[x];
	q[qnt].num=z;
	head[x]=qnt;
}
int find(int x){
	if(g[x]==x)return x;
	g[x]=find(g[x]);
	return g[x];
}
void hqq_dfs(int x){
	int i,j,k;
	vis[x]=1;g[x]=x;
	for(i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y]==0){
			dis[y]=dis[x]+d[i].data;
			hqq_dfs(y);
			g[y]=x;
		}
	}
	mark[x]=1;
	for(i=head[x];i;i=q[i].next){
		int y=q[i].to;
		if(mark[y]){
			ans[q[i].num]=dis[x]+dis[y]-2*dis[find(y)];
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
		hqq_add(j,i,k);
		char c;cin>>c;
	}
	m=read();
	for(i=1;i<=m;i++){
		j=read();k=read();
		hqq_add2(j,k,i);
		hqq_add2(k,j,i);
	}
	hqq_dfs(1);
	for(i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}