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
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=305;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,cnt,num;
int dis[N],h[N],a[N];
struct node{int s,t,data;}e[N*N];
struct edge{int to,next,data;}d[N*N];
void edge_add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
bool BFS(int s,int t){
	memset(dis,-1,sizeof(dis));
	queue<int>q;
	q.push(s);
	dis[s]=0;
	while(q.size()){
		int x=q.front();
		q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]==-1&&d[i].data){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx){
	int ans=0,dlt=0;
	if(x==T||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].data&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[i].data));
			if(dlt==0)dis[y]=-1;
			d[i].data-=dlt;
			d[i^1].data+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){
	int ans=0;
	while(BFS(s,t))ans+=DFS(s,inf);
	return ans;
}
void Build(int maxx){
	cnt=1;
	memset(h,0,sizeof(h));
	for(int i=1;i<=m;i++){
		if(e[i].data<=maxx){
			edge_add(e[i].s,e[i].t,1);
			edge_add(e[i].t,e[i].s,1);
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();num=read();
	S=1;T=n;
	int l=0,r=0,ans=0;
	for(int i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		e[i].data=read();
		r=max(r,e[i].data);
	}
	while(l<=r){
		int mid=(l+r)>>1;
		Build(mid);
		if(Dinic(S,T)>=num){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
}