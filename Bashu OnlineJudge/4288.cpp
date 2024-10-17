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
int n,m,s,t,cnt1,cnt2,h1[10005],h2[10005],vis[10005],dis[10005],p[10005];
struct edge{
	int to,next;
}d1[200005],d2[200005];
void hqq_add1(int x,int y){
	d1[++cnt1]=(edge){y,h1[x]};
	h1[x]=cnt1;
}
void hqq_add2(int x,int y){
	d2[++cnt2]=(edge){y,h2[x]};
	h2[x]=cnt2;
}
void dfs(int x){
	int i,j,k;
	vis[x]=p[x]=0;
	for(i=h2[x];i;i=d2[i].next){
		int y=d2[i].to;
		if(vis[y])dfs(y);
	}
}
queue<int>q;
void spfa(){
	int i,j,k;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	q.push(s);
	while(q.size()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		k=0;
		for(i=h1[x];i;i=d1[i].next){
			int y=d1[i].to;
			if(p[y]){
				k=1;
				break;
			}
		}
		if(k)continue;
//		cout<<x<<endl;
		for(i=h1[x];i;i=d1[i].next){
			int y=d1[i].to;
			if(dis[y]>dis[x]+1){
				dis[y]=dis[x]+1;
				if(!vis[y]){
					q.push(y);
					vis[y]=1;
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
	for(i=1;i<=n;i++)vis[i]=p[i]=1;
	for(i=1;i<=m;i++){
		int x=read(),y=read();
		hqq_add1(x,y);
		hqq_add2(y,x);
	}
	s=read();t=read();
	dfs(t);
	if(vis[s]){
		printf("-1");
		return 0;
	}
	spfa();
	printf("%d",dis[t]);
	return 0;
}