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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
int h[N],fa[N],id[N],dep[N];
int top[N],sum[N],son[N],pos[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Segment_Tree{
	struct Tree{int Max;}t[N*4];
	void Pushup(int p){
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
	}
	void Update(int x,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){t[p].Max=x;return;}
		int mid=(l+r)>>1;
		Update(x,lson);
		Update(x,rson);
		Pushup(p);
	}
	int Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].Max;
		int mid=(l+r)>>1,ans=0;
		ans=max(ans,Ask(x,y,lson));
		ans=max(ans,Ask(x,y,rson));
		return ans;
	}
}Tree;
void DFS1(int x,int depth){
	sum[x]=1;
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;
		DFS1(y,depth+1);
		sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;
	pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
int Ask(int x){
	int ans=0;
	while(x){
		ans=Tree.Ask(id[top[x]],id[x],1,1,n);
		if(ans)return ans;
		x=fa[top[x]];
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=2;i<=n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1,1);
	Tree.Update(id[1],1,1,n);
	while(m--){
		char s[5];
		scanf("%s",s);
		int x=read();
		if(s[0]=='C')Tree.Update(id[x],1,1,n);
		if(s[0]=='Q')printf("%d\n",pos[Ask(x)]);
	}
	return 0;
}
