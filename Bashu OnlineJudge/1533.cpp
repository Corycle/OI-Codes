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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
int a[N],b[N],h[N],rt[N],ans[N];
struct edge{int to,next;}d[N];
struct Tree{int l,r,sum;}t[N*20];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int Merge(int x,int y){
	if(!x||!y)return x+y;
	t[x].sum+=t[y].sum;
	t[x].l=Merge(t[x].l,t[y].l);
	t[x].r=Merge(t[x].r,t[y].r);
	return x;
}
void Insert(int &x,int y,int l,int r){
	if(!x)x=++tot;
	t[x].sum=1;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(y<=mid)Insert(t[x].l,y,l,mid);
	if(y>mid)Insert(t[x].r,y,mid+1,r);
}
int Ask(int x,int y,int p,int l,int r){
	if(!p)return 0;
	if(y<l||x>r)return 0;
	if(x<=l&&r<=y)return t[p].sum;
	int mid=(l+r)>>1,sum=0;
	sum+=Ask(x,y,t[p].l,l,mid);
	sum+=Ask(x,y,t[p].r,mid+1,r);
	return sum;
}
void DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;DFS(y);
		rt[x]=Merge(rt[x],rt[y]);
	}
	ans[x]=Ask(a[x]+1,m,rt[x],1,m);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	for(int i=2;i<=n;i++)Add(read(),i);
	sort(b+1,b+n+1);
	m=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+m+1,a[i])-b;
		Insert(rt[i],a[i],1,m);
	}
	DFS(1);
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}