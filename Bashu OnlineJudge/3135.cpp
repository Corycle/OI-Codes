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
int n,m1,m2,cnt,h[100005],dis[100005],vis[100005];
struct edge{
	int to,next,data;
}d[2000005];
void hqq_add(int x,int y,int z){
	cnt++;
	d[cnt].data=z;
	d[cnt].next=h[x];
	d[cnt].to=y;
	h[x]=cnt;
}
deque<int>q;
void spfa(){
	int i,j,k;
	q.push_back(1);
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	while(q.size()){
		int x=q.front();
		q.pop_front();
		vis[x]=0;
		for(i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>dis[x]+d[i].data){
				dis[y]=dis[x]+d[i].data;
				if(vis[y])continue;
				vis[y]=1;
				if(q.size()){
					if(dis[y]<dis[q.front()])q.push_front(y);
					else q.push_back(y);
				}
				else q.push_back(y);
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m1=read();m2=read();
	for(i=1;i<=m1;i++){
		int x=read(),y=read(),z=read();
		if(x>y)swap(x,y);
		hqq_add(x,y,z);
	}
	for(i=1;i<=m2;i++){
		int x=read(),y=read(),z=read();
		if(x>y)swap(x,y);
		hqq_add(x,y,-z);
	}
	spfa();
	printf("%d\n",dis[n]);
	if(dis[n]<0)printf("YES");
	else printf("NO");
	return 0;
}