#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,num,tot,root[N];
int op[N],b[N],L[N],R[N],c[N];
struct Segment_Tree{
	struct Tree{
		int l,r,sum,tag;
	}t[N*40];
	void Pushup(int p){
		t[p].sum=t[t[p].l].sum+t[t[p].r].sum;
	}
	void Pushdown(int p,int l,int r){
		if(t[p].tag){
			int mid=(l+r)>>1;
			if(!t[p].l)t[p].l=++tot;
			if(!t[p].r)t[p].r=++tot;
			t[t[p].l].tag+=t[p].tag;
			t[t[p].r].tag+=t[p].tag;
			t[t[p].l].sum+=t[p].tag*(mid-l+1);
			t[t[p].r].sum+=t[p].tag*(r-mid);
			t[p].tag=0;
		}
	}
	void Update(int x,int y,int &p,int l,int r){
		if(y<l||r<x)return;
		if(!p)p=++tot;
		if(x<=l&&r<=y){
			t[p].tag++;
			t[p].sum+=r-l+1;
			return;
		}
		Pushdown(p,l,r);
		int mid=(l+r)>>1;
		Update(x,y,t[p].l,l,mid);
		Update(x,y,t[p].r,mid+1,r);
		Pushup(p);
	}
	int Sum(int x,int y,int p,int l,int r){
		if(!p)return 0;
		if(y<l||r<x)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		Pushdown(p,l,r);
		int mid=(l+r)>>1,sum=0;
		sum+=Sum(x,y,t[p].l,l,mid);
		sum+=Sum(x,y,t[p].r,mid+1,r);
		return sum;
	}
}tree;
void Add(int x,int y,int z,int p,int l,int r){
	tree.Update(x,y,root[p],1,n);
	if(l==r)return;
	int mid=(l+r)>>1;
	if(z<=mid)Add(x,y,z,lson);
	else Add(x,y,z,rson);
}
int Ask(int x,int y,int k,int p,int l,int r){
	if(l==r)return b[l];
	int mid=(l+r)>>1;
	int dlt=tree.Sum(x,y,root[p<<1|1],1,n);
	if(dlt<k)return Ask(x,y,k-dlt,lson);
	else return Ask(x,y,k,rson);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		op[i]=read();
		L[i]=read();R[i]=read();c[i]=read();
		if(op[i]==1)b[++num]=c[i];
	}
	sort(b+1,b+num+1);
	num=unique(b+1,b+num+1)-b-1;
	for(int i=1;i<=m;i++){
		if(op[i]==1){
			c[i]=lower_bound(b+1,b+num+1,c[i])-b;
			Add(L[i],R[i],c[i],1,1,num);
		}
		if(op[i]==2){
			printf("%d\n",Ask(L[i],R[i],c[i],1,1,num));
		}
	}
	return 0;
}