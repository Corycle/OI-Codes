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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,cnt=1;
int h[N],dis[N],q[N];
struct edge{
	int to,next,data;
}d[N*20],e[N*20];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
bool BFS(){
	memset(dis,-1,sizeof(dis));
	int l=1,r=1;
	dis[S]=0;
	q[1]=S;
	while(l<=r){
		int x=q[l++];
		if(x==T)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]==-1&&d[i].data){
				dis[y]=dis[x]+1;
				q[++r]=y;
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
int Dinic(){
	int ans=0;
	while(BFS())ans+=DFS(S,inf);
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	S=read()+n;T=read();
	for(int i=1;i<=n;i++){
		Add(i,i+n,1);
		Add(i+n,i,0);
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x+n,y,inf);Add(y,x+n,0);
		Add(y+n,x,inf);Add(x,y+n,0);
	}
	memcpy(e,d,sizeof(e));
	int sum=Dinic();
	printf("%d\n",sum);
	for(int i=1;i<=n;i++){
		if(d[i*2].data==0){//i -> i+n
			memcpy(d,e,sizeof(d));
			d[i*2].data=0;
			if(sum==Dinic()+1){
				e[i*2].data=0;//真正断掉 
				printf("%d ",i);
				sum--;if(!sum)break;
			}
		}
	}
	return 0;
}