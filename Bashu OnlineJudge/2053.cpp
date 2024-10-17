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
const int N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[10];
ll a[N],Ans[33];
int n,m,K,cnt,tot;
struct edge{int to,next;}d[N*2];
int dep[N],sum[N],son[N],top[N];
int h[N],fa[N],st[N],id[N],pos[N];
int nand(int x,int y){return !(x&y);}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
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
struct Tree{bool a[2][2];};
struct Segment_Tree{
	int num;
	Tree t[N*4];
	void Init(int p,int x){
		t[p].a[0][0]=t[p].a[1][0]=nand(0,x);
		t[p].a[0][1]=t[p].a[1][1]=nand(1,x);
	}
	void Pushup(int p){
		int l=p<<1,r=p<<1|1;
		t[p].a[0][0]=t[r].a[0][t[l].a[0][0]];
		t[p].a[0][1]=t[r].a[0][t[l].a[0][1]];
		t[p].a[1][0]=t[l].a[1][t[r].a[1][0]];
		t[p].a[1][1]=t[l].a[1][t[r].a[1][1]];
	}
	void Build(int p,int l,int r){
		if(l==r){Init(p,(a[pos[l]]>>num)&1);return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);Pushup(p);
	}
	void Update(int x,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){Init(p,(a[pos[l]]>>num)&1);return;}
		int mid=(l+r)>>1;Update(x,lson);Update(x,rson);Pushup(p);
	}
	void Query(int x,int y,int type,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Ans[num]=t[p].a[type][Ans[num]];return;}
		int mid=(l+r)>>1;
		if(type==0){Query(x,y,type,lson);Query(x,y,type,rson);}
		if(type==1){Query(x,y,type,rson);Query(x,y,type,lson);}
	}
}tree[33];
ll Query(int x,int y){
	ll ans=0;tot=0;
	memset(Ans,0,sizeof(Ans));
	while(top[x]!=top[y]){
		if(dep[top[x]]>=dep[top[y]]){
			for(int i=0;i<K;i++)tree[i].Query(id[top[x]],id[x],1,1,1,n);
			x=fa[top[x]];
		}
		else{st[++tot]=y;y=fa[top[y]];}
	}
	if(dep[x]<dep[y]){
		for(int i=0;i<K;i++)tree[i].Query(id[x],id[y],0,1,1,n);
	}
	else{
		for(int i=0;i<K;i++)tree[i].Query(id[y],id[x],1,1,1,n);
	}
	while(tot){
		x=top[st[tot]];y=st[tot];tot--;
		for(int i=0;i<K;i++)tree[i].Query(id[x],id[y],0,1,1,n);
	}
	for(int i=0;i<K;i++)ans+=(Ans[i]<<i);
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	DFS1(1,1);DFS2(1,1);
	for(int i=0;i<K;i++){
		tree[i].num=i;
		tree[i].Build(1,1,n);
	}
	while(m--){
		scanf("%s",s);
		if(s[0]=='Q'){
			int x=read(),y=read();
			printf("%lld\n",Query(x,y));
		}
		if(s[0]=='R'){
			int x=read();a[x]=read();
			for(int i=0;i<K;i++)tree[i].Update(id[x],1,1,n);
		}
	}
	return 0;
}