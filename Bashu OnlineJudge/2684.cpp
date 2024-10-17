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
#define ll long long 
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,h[1005],cnt,v[1005],dis[1005],ans;
struct edge{
	int to,next,data;
}d[10005];
void hqq_add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct node{
	int x,num;
};
bool operator<(node x,node y){
	return x.num>y.num;
}
int dp(int maxx){
	memset(dis,0x3f,sizeof(dis));
	priority_queue<node>q;
	q.push((node){1,v[1]});
	while(q.size()){
		int x=q.top().x;
		int num=q.top().num;
		q.pop();
		dis[x]=min(dis[x],num);
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			int p=max(0,num-d[i].data);
			if(p+v[y]>maxx)continue;
			if(p+v[y]<dis[y]){
				dis[y]=p+v[y];
				q.push((node){y,dis[y]});
			}
		}
	}
	if(dis[n]!=inf)return 1;
	else return 0;
}
int main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	srand(time(NULL));
	n=read();m=read();
	for(int i=1;i<=n;i++)v[i]=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		hqq_add(x,y,z);
	}
	int l=0,r=inf;
	while(l<=r){
		int mid=(l+r)>>1;
		if(dp(mid)){
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
}