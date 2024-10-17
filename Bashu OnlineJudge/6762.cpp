/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int Maxn=3e7+5;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
ll Sum[N],Pre[N],dis[N];
int h[N],p[N],fa[N],id[N],pos[N],sum[N];
int son[N],dep[N],top[N],Root[N],pre[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;
		pre[y]=d[i].dist;
		dis[y]=dis[x]+d[i].dist;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
struct Tree{int l,r,sum1;ll sum2;};
struct Segment_Tree{
	int tot;
	Tree t[Maxn];
	void Update(int ql,int qr,int &x,int y,int l,int r){
		x=++tot;t[x]=t[y];
		if(ql<=l&&r<=qr){t[x].sum1++;t[x].sum2+=Pre[r]-Pre[l-1];return;}
		int mid=(l+r)>>1;
		if(ql<=mid)Update(ql,qr,t[x].l,t[y].l,l,mid);
		if(qr>mid)Update(ql,qr,t[x].r,t[y].r,mid+1,r);
		t[x].sum2=t[t[x].l].sum2+t[t[x].r].sum2+(Pre[r]-Pre[l-1])*t[x].sum1;
	}
	ll Query(int x,int y,int tag,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(!p)return (Pre[min(y,r)]-Pre[max(x,l)-1])*tag;
		if(x<=l&&r<=y)return (Pre[r]-Pre[l-1])*tag+t[p].sum2;
		int mid=(l+r)>>1;tag+=t[p].sum1;
		return Query(x,y,tag,t[p].l,l,mid)+Query(x,y,tag,t[p].r,mid+1,r);
	}
}tree;
void Update(int i,int x){
	while(x){
		tree.Update(id[top[x]],id[x],Root[i],Root[i],1,n);
		x=fa[top[x]];
	}
}
ll Query(int i,int x){
	ll ans=dis[x]*i+Sum[i];
//	cout<<"Query: "<<i<<" "<<x<<" "<<ans<<endl;
	while(x){
		ans-=2*tree.Query(id[top[x]],id[x],0,Root[i],1,n);
		x=fa[top[x]];
	}
//	cout<<"Query: "<<i<<" "<<x<<" "<<ans<<endl;
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)p[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	DFS1(1,1);DFS2(1,1);
	for(int i=1;i<=n;i++){
		Sum[i]=Sum[i-1]+dis[p[i]];
		Pre[i]=Pre[i-1]+pre[pos[i]];
	}
	for(int i=1;i<=n;i++){Root[i]=Root[i-1];Update(i,p[i]);}
	ll Ans=0;
	while(m--){
		int op=read();
		if(op==1){
			int l=read()^Ans,r=read()^Ans,x=read()^Ans;
//			cout<<Query(l-1,x)<<" "<<Query(r,x)<<endl;
			printf("%lld\n",Ans=Query(r,x)-Query(l-1,x));
			Ans&=((1<<30)-1);
		}
		if(op==2){
			int x=read()^Ans;
			swap(p[x],p[x+1]);
			Sum[x]=Sum[x-1]+dis[p[x]];
			Root[x]=Root[x-1];Update(x,p[x]);
		}
	}
	return 0;
}