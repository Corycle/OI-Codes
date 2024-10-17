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
#define inf 0x7f7f7f7f7f7f7f7f
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
long long read(){
	long long s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
long long m,n,s,t,L,cnt;
long long v[10005],h[10005],dis[10005],vis[10005];
struct edge{
	long long to,next,data;
}d[100005];
void hqq_add(long long x,long long y,long long z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct node{
	long long city,dist;
};
bool operator<(node x,node y){
	return x.dist>y.dist;
}
priority_queue<node>q;
int dij(long long p){
	int i,j,k;
	if(v[s]>p||v[t]>p)return 0;
	memset(dis,0x7f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	node st=(node){s,0};
	q.push(st);
	dis[s]=0;
	while(q.size()){
		long long x=q.top().city;
//		cout<<x<<" "<<dis[x]<<endl;
		q.pop();vis[x]=0;
		for(i=h[x];i;i=d[i].next){
			long long y=d[i].to;
			if(v[y]>p)continue;
			if(dis[x]+d[i].data<dis[y]){
				dis[y]=dis[x]+d[i].data;
				if(!vis[y]){
					vis[y]=1;
					q.push((node){y,dis[y]});
				}
			}
		}
	}
//	cout<<dis[t]<<endl;
	if(dis[t]>L)return 0;
	return 1;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	s=read();t=read();L=read();
	long long l=inf,r=0;
	for(i=1;i<=n;i++){
		v[i]=read();
		r=max(r,v[i]);
		l=min(l,v[i]);
	}
	for(i=1;i<=m;i++){
		long long x=read(),y=read(),z=read();
		hqq_add(x,y,z);
		hqq_add(y,x,z);
	}
	if(!dij(r)){
		printf("-1");
		return 0;
	}
	while(l<=r){
		int mid=l+r>>1;
		if(dij(mid))r=mid-1;
		else l=mid+1;
	}
	printf("%lld",r+1);
	return 0;
}