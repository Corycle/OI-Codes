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
const int Lim=450000;
const int N=450005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,st,a[N],sum[N];
struct Tree{int Min,num,ans,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void Pushup(int p){
		t[p].ans=t[p<<1].ans+t[p<<1|1].ans;
		t[p].Min=min(t[p<<1].Min,t[p<<1|1].Min);
		t[p].num=(t[p<<1].Min==t[p].Min)*t[p<<1].num+(t[p<<1|1].Min==t[p].Min)*t[p<<1|1].num;
	}
	void update(int p,int x){
		t[p].Min+=x;
		t[p].tag+=x;
		t[p].ans=(t[p].Min==0)*t[p].num;
	}
	void Pushdown(int p){
		if(t[p].tag){
			update(p<<1,t[p].tag);
			update(p<<1|1,t[p].tag);
			t[p].tag=0;
		}
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].num=1;t[p].ans=1;return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		Pushup(p);
	}
	void Update(int x,int y,int val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,val);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,val,lson);Update(x,y,val,rson);
		Pushup(p);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].ans;
		int mid=(l+r)>>1;Pushdown(p);
		return Query(x,y,lson)+Query(x,y,rson);
	}
}tree;
void Change(int x,int val){
	if(x<=st+n){
		int pos=x-sum[x]+1-(val>0);
		tree.Update(pos,pos,val,1,1,Lim);
	}
	sum[x]+=val;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();st=150000;
	tree.Build(1,1,Lim);
	for(int i=1;i<=n;i++){
		a[i]=st+read();
		Change(a[i],1);
	}
	while(m--){
		int p=read(),x=read();
		if(p==0){
			if(x==1){
				int pos=st+n;
				if(sum[pos])tree.Update(pos-sum[pos]+1,pos,-1,1,1,Lim);
				st--;
			}
			if(x==-1){
				st++;
				int pos=st+n;
				if(sum[pos])tree.Update(pos-sum[pos]+1,pos,1,1,1,Lim);
			}
		}
		else{
			Change(a[p],-1);
			a[p]=st+x;
			Change(a[p],1);
		}
		printf("%d\n",tree.Query(st+1,st+n,1,1,Lim));
	}
	return 0;
}