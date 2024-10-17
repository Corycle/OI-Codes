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
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
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
int n,m,p,cnt,cnt2,ans=inf;
int h[3005],h2[3005],vis[3005][3005],dis[3005][3005];
struct edge{
	int to,next;
}d[40005];
struct node{
	int to,next,last;
}k[100005];
void hqq_add1(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void hqq_add2(int z,int x,int y){//z->x->y
	k[++cnt2]=(node){y,h2[x],z};
	h2[x]=cnt2;
}
struct direction{
	int last,now;
};
bool operator<(direction x,direction y){
	return dis[x.last][x.now]>dis[y.last][y.now];
}
void dij(){
	memset(dis,0x3f,sizeof(dis));
	dis[0][1]=0;
	priority_queue<direction>q;
	q.push((direction){0,1});
	while(q.size()){
		direction x=q.top();
		if(x.now==n){
			ans=min(ans,dis[x.last][x.now]);
		}
		q.pop();
		vis[x.last][x.now]=0;
		for(int i=h[x.now];i;i=d[i].next){
			int fl=x.now,fn=d[i].to;
			bool flag=false;
			for(int j=h2[x.now];j;j=k[j].next){
				if(k[j].last==x.last&&k[j].to==fn){
					flag=true;
					break;
				}
			}
			if(flag)continue;
			if(dis[fl][fn]>dis[x.last][x.now]+1){
				dis[fl][fn]=dis[x.last][x.now]+1;
				if(!vis[fl][fn]){
					vis[fl][fn]=1;
					q.push((direction){fl,fn});
				}
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		hqq_add1(x,y);
		hqq_add1(y,x);
	}
	for(int i=1;i<=p;i++){
		int x=read(),y=read(),z=read();
		hqq_add2(x,y,z);
	}
	dij();
	printf("%d",ans);
	return 0;
}