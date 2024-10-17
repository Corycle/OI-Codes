#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=5000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
	建立两棵线段树，
	A树从所有节点向父亲连边，
	B树从所有节点向儿子连边，
	从B树的所有叶子向A树的所有叶子连边，
	边权都是0。
	
	对于每个操作，新建节点c，
	从A中对应的节点向c连边，
	从c向B中对应的节点连边，
	边权都是1
	
	然后跑Dijkstra就行了，最后ans/2。
*/
int n,m,S,cnt;
int h[N],vis[N],dis[N],pos[N];
struct edge{
	int to,next,data;
}d[N*5];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct Segment_Tree{
	void Build(int p,int l,int r,int flag){
		if(l==r){
			if(flag)Add(p+n*4,p,0);
			else pos[l]=p;
			return;
		}
		int mid=(l+r)>>1;
		Build(lson,flag);
		Build(rson,flag);
		if(flag){
			Add(p+n*4,(p<<1)+n*4,0);
			Add(p+n*4,(p<<1|1)+n*4,0);
		}
		else{
			Add(p<<1,p,0);
			Add(p<<1|1,p,0);
		}
	}
	void Update(int x,int y,int c,int p,int l,int r,int flag){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			if(flag)Add(c,p+n*4,1);
			else Add(p,c,1);
			return;
		}
		int mid=(l+r)>>1;
		Update(x,y,c,lson,flag);
		Update(x,y,c,rson,flag);
	}
}T1,T2;
struct cmp{
	bool operator()(int x,int y){
		return dis[x]>dis[y];
	}
};
void Dijkstra(){
	priority_queue<int,vector<int>,cmp>q;
	memset(dis,0x3f,sizeof(dis));
	q.push(pos[S]);dis[pos[S]]=0;
	while(q.size()){
		int x=q.top();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>dis[x]+d[i].data){
				dis[y]=dis[x]+d[i].data;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();S=read();
	T1.Build(1,1,n,0);
	T2.Build(1,1,n,1);
	int tot=n*8;
	for(int i=1;i<=m;i++){
		int a=read(),b=read(),c=read(),d=read();
		T1.Update(a,b,++tot,1,1,n,0);T2.Update(c,d,tot,1,1,n,1);
		T1.Update(c,d,++tot,1,1,n,0);T2.Update(a,b,tot,1,1,n,1);
	}
	Dijkstra();
	for(int i=1;i<=n;i++){
		printf("%d\n",dis[pos[i]]/2);
	}
	return 0;
}