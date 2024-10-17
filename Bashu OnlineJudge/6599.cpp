/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
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
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,type,Ans,Root[N];
struct Tree1{int sum,tag;};
struct Segment_Tree1{
	Tree1 t[N*4];
	void update(int p,int l,int r,int val){
		t[p].tag=val;
		t[p].sum=(r-l+1)*val;
	}
	void Pushdown(int p,int l,int r){
		if(t[p].tag){
			int mid=(l+r)>>1;
			update(lson,t[p].tag);
			update(rson,t[p].tag);
			t[p].tag=0;
		}
	}
	void Update(int x,int y,int val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,l,r,val);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Update(x,y,val,lson);Update(x,y,val,rson);
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p,l,r);
		return Query(x,y,lson)+Query(x,y,rson);
	}
}tree1;
struct Tree2{int l,r,tim,val;};
struct Segment_Tree2{
	int tot;
	Tree2 t[N*80];
	void Pushdown(int p){
		if(t[p].tim){
			t[++tot]=(Tree2){t[t[p].l].l,t[t[p].l].r,t[p].tim,t[p].val};t[p].l=tot;
			t[++tot]=(Tree2){t[t[p].r].l,t[t[p].r].r,t[p].tim,t[p].val};t[p].r=tot;
			t[p].tim=0;
		}
	}
	void Update(int ql,int qr,int tim,int val,int &x,int y,int l,int r){
		x=++tot;
		if(ql<=l&&r<=qr){t[x].tim=tim;t[x].val=val;return;}
		int mid=(l+r)>>1;if(y)Pushdown(y);t[x].l=t[y].l;t[x].r=t[y].r;
		if(ql<=mid)Update(ql,qr,tim,val,t[x].l,t[y].l,l,mid);
		if(qr>mid)Update(ql,qr,tim,val,t[x].r,t[y].r,mid+1,r);
	}
	int Query(int x,int p,int l,int r){
		if(!p||t[p].tim)return p;
		int mid=(l+r)>>1;
		if(x<=mid)return Query(x,t[p].l,l,mid);
		return Query(x,t[p].r,mid+1,r);
	}
}tree2;
int main(){
//	freopen("train.in","r",stdin);
//	freopen("train.out","w",stdout);
	n=read();m=read();type=read();
	for(int i=1;i<=m;i++){
		int op=read();
		Root[i]=Root[i-1];
		if(op==1){
			int l=(read()+Ans*type)%n+1;
			int r=(read()+Ans*type)%n+1;
			if(l>r)swap(l,r);
			printf("%d\n",Ans=tree1.Query(l,r,1,1,n));
		}
		if(op==2){
			int x=(read()+Ans*type)%n+1;
			int pos=tree2.Query(x,Root[i-1],1,n);
			if(!pos)continue;
			int pre=tree2.Query(x,Root[tree2.t[pos].tim-1],1,n);
			tree2.Update(x,x,tree2.t[pre].tim,tree2.t[pre].val,Root[i],Root[i],1,n);
			tree1.Update(x,x,tree2.t[pre].val,1,1,n);
		}
		if(op==3){
			int l=(read()+Ans*type)%n+1;
			int r=(read()+Ans*type)%n+1;
			int x=read();if(l>r)swap(l,r);
			tree2.Update(l,r,i,x,Root[i],Root[i],1,n);
			tree1.Update(l,r,x,1,1,n);
		}
	}
	return 0;
}