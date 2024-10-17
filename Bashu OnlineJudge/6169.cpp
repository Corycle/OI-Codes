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
const int N=100005;
const int M=32;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,root[N];
struct Tree{int l,r,sum;};
struct Segment_Tree{
	Tree t[N*M];
	void Insert(int x,int &y,int val,int l,int r){
		y=++tot;t[y]=t[x];t[y].sum+=val;
		if(l==r)return;int mid=(l+r)>>1;
		if(val<=mid)Insert(t[x].l,t[y].l,val,l,mid);
		if(val>mid)Insert(t[x].r,t[y].r,val,mid+1,r);
	}
	int Ask(int x,int y,int ql,int qr,int l,int r){
		if(qr<l||ql>r||!(t[y].sum-t[x].sum))return 0;
		if(ql<=l&&r<=qr)return t[y].sum-t[x].sum;
		int mid=(l+r)>>1,ans=0;
		if(ql<=mid)ans+=Ask(t[x].l,t[y].l,ql,qr,l,mid);
		if(qr>mid)ans+=Ask(t[x].r,t[y].r,ql,qr,mid+1,r);
		return ans;
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		tree.Insert(root[i-1],root[i],read(),1,inf);
	}
	m=read();
	while(m--){
		int l=read(),r=read();
		int lst=1,ans=1;
		while(1){
			int sum=tree.Ask(root[l-1],root[r],lst,ans,1,inf);
			lst=ans+1;ans+=sum;if(!sum)break;
		}
		printf("%d\n",ans);
	}
	return 0;
}