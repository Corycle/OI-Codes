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
using namespace std;
const int inf=0x3f3f3f3f;
const int Lim=1e5;
const int N=1e5+5;
const int M=20;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Sum;
int n,m,Root[N];
struct Node{int d,v,l;}P[N];
bool cmp(Node A,Node B){return A.d<B.d;}
struct Tree{int l,r;ll sum,ans;};
struct Segment_Tree{
	int tot;
	Tree t[N*M];
	void Insert(int pos,int val,int &x,int y,int l,int r){
		x=++tot;t[x]=t[y];t[x].sum+=val;t[x].ans+=1ll*pos*val;
		if(l==r)return;int mid=(l+r)>>1;
		if(pos<=mid)Insert(pos,val,t[x].l,t[y].l,l,mid);
		if(pos>mid)Insert(pos,val,t[x].r,t[y].r,mid+1,r);
	}
	ll Query(ll k,int x,int y,int l,int r){
		if(l==r)return 1ll*k*l;
		int mid=(l+r)>>1;
		ll sum=t[t[y].l].sum-t[t[x].l].sum;
		ll ans=t[t[y].l].ans-t[t[x].l].ans;
		if(k<=sum)return Query(k,t[x].l,t[y].l,l,mid);
		return ans+Query(k-sum,t[x].r,t[y].r,mid+1,r);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		P[i].d=read();
		P[i].v=read();
		P[i].l=read();
		Sum+=P[i].l;
	}
	sort(P+1,P+n+1,cmp);
	for(int i=1;i<=n;i++){
		tree.Insert(P[i].v,P[i].l,Root[i],Root[i-1],1,Lim);
	}
	while(m--){
		ll G=read(),L=read();
		int l=1,r=n,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(Sum-tree.t[Root[mid-1]].sum>=L&&tree.Query(L,Root[mid-1],Root[n],1,Lim)<=G){
				ans=mid;l=mid+1;
			}
			else r=mid-1;
		}
		printf("%d\n",ans?P[ans].d:-1);
	}
	return 0;
}