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
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=998244353;
const int Inv=796898467;//Inv 1e4
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p1,p2,tot;
int a[N],v[N],rt[N],fa[N],ch[N][2];
int Sqr(int x){return 1ll*x*x%Mod;}
struct Tree{int l,r;ll tag,ans;};
struct Segment_Tree{
	Tree t[N*20];
	void update(int p,int x){
		t[p].tag=t[p].tag*x%Mod;
		t[p].ans=t[p].ans*x%Mod;
	}
	void Pushdown(int p){
		if(t[p].l)update(t[p].l,t[p].tag);
		if(t[p].r)update(t[p].r,t[p].tag);
		t[p].tag=1;
	}
	void Insert(int &p,int l,int r,int x){
		if(!p)p=++tot;t[p].tag=1;t[p].ans=1;
		if(l==r)return;int mid=(l+r)>>1;
		if(x<=mid)Insert(lson,x);else Insert(rson,x);
	}
	int Merge(int x,int y,int sx,int sy){
		if(!x||!y){
			if(x)update(x,sy);
			if(y)update(y,sx);
			return x|y;
		}
		Pushdown(x);Pushdown(y);
		int pxl=t[t[x].l].ans*p1%Mod,pxr=t[t[x].r].ans*p2%Mod;
		int pyl=t[t[y].l].ans*p1%Mod,pyr=t[t[y].r].ans*p2%Mod;
		t[x].l=Merge(t[x].l,t[y].l,(pxr+sx)%Mod,(pyr+sy)%Mod);
		t[x].r=Merge(t[x].r,t[y].r,(pxl+sx)%Mod,(pyl+sy)%Mod);
		t[x].ans=(t[t[x].l].ans+t[t[x].r].ans)%Mod;
		return x;
	}
	int Ask(int p,int l,int r){
		if(l==r)return 1ll*l*a[l]%Mod*Sqr(t[p].ans)%Mod;
		int mid=(l+r)>>1;Pushdown(p);
		return (Ask(lson)+Ask(rson))%Mod;
	}
}tree;
void DFS(int x){
	if(!ch[x][0]){
		int pos=lower_bound(a+1,a+a[0]+1,v[x])-a;
		tree.Insert(rt[x],1,a[0],pos);
		return;
	}
	DFS(ch[x][0]);
	if(!ch[x][1]){rt[x]=rt[ch[x][0]];return;}
	DFS(ch[x][1]);
	p1=v[x];p2=(1-v[x]+Mod)%Mod;
	rt[x]=tree.Merge(rt[ch[x][0]],rt[ch[x][1]],0,0);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		fa[i]=read();
		if(!ch[fa[i]][0])ch[fa[i]][0]=i;
		else ch[fa[i]][1]=i;
	}
	for(int i=1;i<=n;i++){
		v[i]=read();
		if(!ch[i][0])a[++a[0]]=v[i];
		else v[i]=1ll*v[i]*Inv%Mod;
	}
	sort(a+1,a+a[0]+1);DFS(1);
	printf("%d",tree.Ask(rt[1],1,a[0]));
	return 0;
}