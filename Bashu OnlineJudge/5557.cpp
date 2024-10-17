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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Q,top,st[N],pos[N];
struct Segment_Tree{
	int t[N*4];
	void Build(int p,int l,int r){
		if(l==r){t[p]=pos[l];return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p]=max(t[p<<1],t[p<<1|1]);
	}
	int Ask(int x,int p,int l,int r){
		if(t[p]<=x)return 0;
		if(l==r)return l;
		int mid=(l+r)>>1;
		if(t[p<<1|1]>x)return Ask(x,rson);
		return Ask(x,lson);
	}
	int Query(int x,int y,int z,int p,int l,int r){
		if(x<=l&&r<=y)return Ask(z,p,l,r);
		int mid=(l+r)>>1,ans=0;
		if(y>mid)ans=Query(x,y,z,rson);
		if(ans)return ans;
		if(x<=mid)ans=Query(x,y,z,lson);
		return ans;
	}
}tree;
int L[N],R[N],l[N],r[N];
int Query(int l,int r,int x){
	//Query for the last P in [l,r] that pos[P]>x;
	if(l>r)return l;
	int Pos=tree.Query(l,r,x,1,1,n);
	return Pos?Pos+1:l;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		pos[x]=y;
	}
	tree.Build(1,1,n);
	pos[0]=-1;pos[n]=n+1;
	for(int i=1;i<=n;i++){
		if(!pos[i-1]||pos[i-1]>i-1)L[i]=L[i-1];
		else L[i]=i;
	}
	for(int i=n;i>=1;i--){
		if(!pos[i]||pos[i]<=i)R[i]=R[i+1];
		else R[i]=i;
	}
	for(int i=n;i>=1;i--){
		l[i]=r[i]=i;
		l[i]=Query(L[i],l[i]-1,r[i]);
		st[++top]=i;
		while(top&&(!pos[st[top]]||(l[i]<=pos[st[top]]&&pos[st[top]]<=r[i]))){
			r[i]=st[--top];
			l[i]=Query(L[i],l[i]-1,r[i]);
		}
	}
	while(Q--){
		int x=read(),y=read();
		if(l[x]<=y&&y<=r[x])puts("YES");
		else puts("NO");
	}
	return 0;
}