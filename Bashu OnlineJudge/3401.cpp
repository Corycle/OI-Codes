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
const int N=30005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,total,maxx,tot=1;
int root[N],val[N],sum[N];
struct Tree{
	int l,r,sum;
}t[N*200];
int Add(int data,int addv,int x,int l,int r){
	int y=++tot;
	t[y].sum=t[x].sum+addv;
	if(l==r)return y;
	int mid=(l+r)>>1;
	t[y].l=t[x].l;t[y].r=t[x].r;
	if(data<=mid)t[y].l=Add(data,addv,t[x].l,l,mid);
	else t[y].r=Add(data,addv,t[x].r,mid+1,r);
	return y;
}
int Ask(int L,int R,int x,int y,int l,int r){
	if(R<l||r<L)return 0;
	if(L<=l&&r<=R)return t[y].sum-t[x].sum;
	int mid=(l+r)>>1,ans=0;
	ans+=Ask(L,R,t[x].l,t[y].l,l,mid);
	ans+=Ask(L,R,t[x].r,t[y].r,mid+1,r);
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	root[0]=1;
	for(int i=1;i<=n;i++){
		val[i]=read();
		sum[i]=read();
		maxx=max(maxx,val[i]);
	}
	for(int i=1;i<=n;i++){
		root[i]=Add(val[i],sum[i],root[i-1],1,maxx);
	}
	m=read();
	while(m--){
		int sx=read(),sy=read();
		int fx=read(),fy=read(),k=read();
		int l=fx,r=fy,ans=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			int dlt=Ask(fx,mid,root[sx-1],root[sy],1,maxx);
			if(dlt>=k){
				ans=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
3
1 5
2 5
3 5
5
1 2 1 3 6
1 2 2 3 2
2 3 1 3 4
2 3 1 3 7
2 3 1 3 11
*/