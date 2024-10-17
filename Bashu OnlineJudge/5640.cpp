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
const int Lim=1000000;
const int N=500005;
const int M=25;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Root[N];
struct Tree{int l,r,tot;ll sum;};
struct Segment_Tree{
	int tot;
	Tree t[N*M];
	void Insert(int v,int &x,int y,int l,int r){
		x=++tot;t[x]=t[y];t[x].tot++;t[x].sum+=v;
		if(l==r)return;int mid=(l+r)>>1;
		if(v<=mid)Insert(v,t[x].l,t[y].l,l,mid);
		if(v>mid)Insert(v,t[x].r,t[y].r,mid+1,r);
	}
	ll Query(int k,int f,int x,int y,int l,int r){
		if(!(t[y].tot-t[x].tot))return 0;
		ll tot=t[y].tot-t[x].tot,sum=t[y].sum-t[x].sum;
		if(l>=f+k)return sum-((k+f)+(k+f+tot-1))*tot/2;
		if(r<=f+k+tot-1)return ((k+f)+(k+f+tot-1))*tot/2-sum;
		int mid=(l+r)>>1,lsum=t[t[y].l].tot-t[t[x].l].tot;
		return Query(k,f,t[x].l,t[y].l,l,mid)+Query(k,f+lsum,t[x].r,t[y].r,mid+1,r);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		tree.Insert(read(),Root[i],Root[i-1],1,Lim);
	}
	while(m--){
		int l=read(),r=read(),k=read();
		printf("%lld\n",tree.Query(k,0,Root[l-1],Root[r],1,Lim));
	}
	return 0;
}