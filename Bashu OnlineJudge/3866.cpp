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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,num,tot,cnt=1;
int h[N],A[N],b[N],L[N],R[N],dis[N],root[N];
struct edge{int to,next,flow;}d[N*5];
struct Tree{int l,r,sum;}t[N*5];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	memset(dis,-1,sizeof(dis));
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	int ans=0,dlt=0;
	if(x==t||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){
	int ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
void Ask(int x,int l,int r,int fx,int fy,int p){
	if(!x||fy<l||r<fx)return;
	if(fx<=l&&r<=fy){
		Add(x,p,inf);
		return;
	}
	int mid=(l+r)>>1;
	Ask(t[x].l,l,mid,fx,fy,p);
	Ask(t[x].r,mid+1,r,fx,fy,p);
}
void Insert(int &x,int y,int l,int r,int fx,int p,int fa){
	x=++tot;
	t[x]=t[y];Add(y,x,inf);
	if(fa)Add(x,fa,inf);
	if(l==r){
		Add(p,x,inf);
		return;
	}
	int mid=(l+r)>>1;
	if(fx<=mid)Insert(t[x].l,t[y].l,l,mid,fx,p,x);
	else Insert(t[x].r,t[y].r,mid+1,r,fx,p,x);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	int S=n*2+1,T=n*2+2;
	int ans=0;tot=T;
	for(int i=1;i<=n;i++){
		int B,W,P;
		A[i]=read();B=read();W=read();
		L[i]=read();R[i]=read();P=read();
		Add(S,i,W);Add(i,T,B);Add(i+n,i,P);
		b[++num]=A[i];b[++num]=L[i];b[++num]=R[i];
		ans+=B+W;
	}
	sort(b+1,b+num+1);
	num=unique(b+1,b+num+1)-b-1;
	for(int i=1;i<=n;i++){
		int a=lower_bound(b+1,b+num+1,A[i])-b;
		int l=lower_bound(b+1,b+num+1,L[i])-b;
		int r=lower_bound(b+1,b+num+1,R[i])-b;
		Ask(root[i-1],1,num,l,r,i+n);
		Insert(root[i],root[i-1],1,num,a,i,0);
	}
	ans-=Dinic(S,T);
	printf("%d",ans);
	return 0;
}