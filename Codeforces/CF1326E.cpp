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
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Ans,a[N],b[N],c[N];
struct Node{int Max,tag;};
struct Segment_Tree{
	Node t[N*4];
	void update(int p,int x){t[p].Max+=x;t[p].tag+=x;}
	void Pushdown(int p){if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}}
	void Update(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,z);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,z,lson);Update(x,y,z,rson);
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Ans=n;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)c[a[i]]=i;
	printf("%d ",Ans);
	tree.Update(1,c[n],1,1,1,n);
	for(int i=1;i<n;i++){
		tree.Update(1,b[i],-1,1,1,n);
		while(tree.t[1].Max<=0){
			Ans--;
			tree.Update(1,c[Ans],1,1,1,n);
		}
		printf("%d ",Ans);
	}
	return 0;
}
