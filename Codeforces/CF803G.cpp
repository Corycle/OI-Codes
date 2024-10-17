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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Lim,Root,a[N],p[N][20];
void ST(){
	for(int i=1;i<=n;i++)p[i][0]=a[i];
	for(int j=1;j<20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			p[i][j]=min(p[i][j-1],p[i+(1<<(j-1))][j-1]);
		}
	}
}
int Min(int l,int r){
	int k=(int)(log(r-l+1)/log(2));
	return min(p[l][k],p[r-(1<<k)+1][k]);
}
int Ask(int l,int r){
	if(r>=l+n-1)return Min(1,n);
	l%=n;r%=n;if(!l)l=n;if(!r)r=n;
	return l<=r?Min(l,r):min(Min(l,n),Min(1,r));
}
struct Tree{int l,r,tag,Min;};
struct Segment_Tree{
	int tot;
	Tree t[N*60];
	void update(int p,int v){t[p].tag=t[p].Min=v;}
	void Init(int &p,int l,int r){p=++tot;t[p].Min=Ask(l,r);}
	void Pushdown(int p,int l,int r){
		int mid=(l+r)>>1;
		if(!t[p].l)Init(lson);
		if(!t[p].r)Init(rson);
		if(t[p].tag){
			update(t[p].l,t[p].tag);
			update(t[p].r,t[p].tag);
			t[p].tag=0;
		}
	}
	void Update(int x,int y,int v,int &p,int l,int r){
		if(!p)Init(p,l,r);
		if(x<=l&&r<=y){update(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		if(x<=mid)Update(x,y,v,lson);
		if(y>mid) Update(x,y,v,rson);
		t[p].Min=min(t[t[p].l].Min,t[t[p].r].Min);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return inf;
		if(x<=l&&r<=y)return p?t[p].Min:Ask(l,r);
		int mid=(l+r)>>1;Pushdown(p,l,r);
		return min(Query(x,y,lson),Query(x,y,rson));
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Lim=n*m;
	for(int i=1;i<=n;i++)a[i]=read();
	int T=read();ST();tree.t[0].Min=inf;
	while(T--){
		int op=read(),l=read(),r=read();
		if(op==1)tree.Update(l,r,read(),Root,1,Lim);
		if(op==2)printf("%d\n",tree.Query(l,r,Root,1,Lim));
	}
	return 0;
}
