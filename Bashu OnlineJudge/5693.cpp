/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=300005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
ll f[N];
int n,tot,top1,top2;
int a[N],st1[N],st2[N],root[N];
struct BIT{
	int c[N];
	inline int lowbit(int x){return x&(-x);}
	inline void Add(int x){for(int i=x;i<=n;i+=lowbit(i))c[i]++;}
	inline int Ask(int x){int ans=0;for(int i=x;i>=1;i-=lowbit(i))ans+=c[i];return ans;}
}tree;
struct Segment_Tree{
	struct Tree{int l,r,sum;}t[N*20];
	void Insert(int &x,int y,int pos,int l,int r){
		x=++tot;t[x]=t[y];t[x].sum++;
		if(l==r)return;int mid=(l+r)>>1;
		if(pos<=mid)Insert(t[x].l,t[y].l,pos,l,mid);
		else Insert(t[x].r,t[y].r,pos,mid+1,r);
	}
	int Ask(int p,int x,int y,int l,int r){
		if(x>y)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;
		if(y<=mid)return Ask(t[p].l,x,y,l,mid);
		if(x>mid)return Ask(t[p].r,x,y,mid+1,r);
		return Ask(t[p].l,x,y,l,mid)+Ask(t[p].r,x,y,mid+1,r);
	}
}Tree;
int Ask(int x,int y){
	x=st1[x];y=st2[y];
	if(y<x||a[x]<a[y])return 0;
	int tmp1=Tree.Ask(root[y-1],a[y]+1,a[x]-1,1,n);
	int tmp2=Tree.Ask(root[x],a[y]+1,a[x]-1,1,n);
	return tmp1-tmp2;
}
void Solve(int ql,int qr,int l,int r){
	if(l>r)return;
	int mid=(l+r)>>1,id=0,tmp=0;
	for(int i=ql;i<=qr;i++){
		tmp=Ask(i,mid);
		if(tmp>f[mid]){
			f[mid]=tmp;id=i;
		}
	}
	if(!id)return;
	Solve(ql,id,l,mid-1);
	Solve(id,qr,mid+1,r);
}
int main(){
//	freopen("fire.in","r",stdin);
//	freopen("fire.out","w",stdout);
	ll sum=0;n=read();
	for(register int i=1;i<=n;i++){
		a[i]=read();
		sum+=i-1-tree.Ask(a[i]);tree.Add(a[i]);
		Tree.Insert(root[i],root[i-1],a[i],1,n);
	}
	ll Max=0;
	for(register int i=1;i<=n;i++)if(!top1||a[st1[top1]]<a[i])st1[++top1]=i;
	for(register int i=n;i>=1;i--)if(!top2||a[st2[top2]]>a[i])st2[++top2]=i;
	for(register int i=1;i<=top2/2;i++)swap(st2[i],st2[top2-i+1]);
	Solve(1,top1,1,top2);
	for(register int i=1;i<=top2;i++)Max=max(Max,f[i]);
	printf("%lld",sum-Max*2);
	return 0;
}