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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[10];
int n,m,cnt,tot;
int h[N],a[N],fa[N],id[N],pos[N],dep[N],sum[N],top[N],son[N],Pos[N];
struct edge{int to,next,dist,id;}d[N*2];
void Add(int x,int y,int z,int id){
	d[++cnt]=(edge){y,h[x],z,id};h[x]=cnt;
}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
		Pos[d[i].id]=y;a[y]=d[i].dist;
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
struct Tree{int tag1,tag2,Max;};
struct Segment_Tree{
	Tree t[N*4];
	void update1(int p,int x){t[p].Max+=x;if(t[p].tag2)t[p].tag2+=x;else t[p].tag1+=x;}
	void update2(int p,int x){t[p].Max=x;if(t[p].tag1)t[p].tag1=0;t[p].tag2=x;}
	void Pushdown(int p){
		if(t[p].tag1){update1(p<<1,t[p].tag1);update1(p<<1|1,t[p].tag1);t[p].tag1=0;}
		if(t[p].tag2){update2(p<<1,t[p].tag2);update2(p<<1|1,t[p].tag2);t[p].tag2=0;}
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].Max=a[pos[l]];return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
	}
	void Update(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update1(p,z);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,z,lson);Update(x,y,z,rson);
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
	}
	void Change(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update2(p,z);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Change(x,y,z,lson);Change(x,y,z,rson);
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].Max;
		int mid=(l+r)>>1;Pushdown(p);
		return max(Query(x,y,lson),Query(x,y,rson));
	}
}tree;
void Update(int x,int y,int z){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		tree.Update(id[top[x]],id[x],z,1,1,n);
		if(fa[top[x]]==y)return;x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	tree.Update(id[son[x]],id[y],z,1,1,n);
}
void Change(int x,int y,int z){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		tree.Change(id[top[x]],id[x],z,1,1,n);
		if(fa[top[x]]==y)return;x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	tree.Change(id[son[x]],id[y],z,1,1,n);
}
int Query(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=max(ans,tree.Query(id[top[x]],id[x],1,1,n));
		if(fa[top[x]]==y)return ans;x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return max(ans,tree.Query(id[son[x]],id[y],1,1,n));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z,i);Add(y,x,z,i);
	}
	DFS1(1,1);DFS2(1,1);
	tree.Build(1,1,n);
	while(1){
		scanf("%s",s);
		if(s[0]=='S')break;
		if(s[0]=='M')printf("%d\n",Query(read(),read()));
		if(s[0]=='A'){int x=read(),y=read(),z=read();Update(x,y,z);}
		if(s[1]=='o'){int x=read(),y=read(),z=read();Change(x,y,z);}
		if(s[1]=='h'){int k=read(),x=read();tree.Change(id[Pos[k]],id[Pos[k]],x,1,1,n);}
	}
	return 0;
}