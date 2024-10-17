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
#include<set>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
#define set_it set<int>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int M=1e6+5;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
set<int>S;
int n,m,Q,a[N],b[N],L[M],R[M],id[N],tmp[N];
bool cmp(int x,int y){return b[x]!=b[y]?b[x]<b[y]:x<y;}
struct Tree{int Min,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void Clear(){memset(t,0,sizeof(t));}
	void update(int p,int v){t[p].Min+=v;t[p].tag+=v;}
	void Pushdown(int p){if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}}
	void Update(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,v,lson);Update(x,y,v,rson);
		t[p].Min=min(t[p<<1].Min,t[p<<1|1].Min);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=0;i<=n+1;i++)a[i]=i;
	for(int i=1;i<n;i++)S.insert(i);
	for(int i=1;i<=m;i++){L[i]=read();R[i]=read();}
	for(int i=m;i>=1;i--){
		int l=L[i],r=R[i];
		while(1){
			set_it p=S.lower_bound(l);
			if(p==S.end()||(*p)>=r)break;
			int pos=(*p);swap(a[pos],a[pos+1]);
			S.erase(pos-1);S.erase(pos);S.erase(pos+1);
			if(a[pos-1]<a[pos])S.insert(pos-1);
			if(a[pos+1]<a[pos+2])S.insert(pos+1);
		}
	}
	for(int i=1;i<=n;i++)id[a[i]]=i;
	while(Q--){
		for(int i=1;i<=n;i++){b[i]=read();tmp[i]=i;}
		sort(tmp+1,tmp+n+1,cmp);tree.Clear();
		bool flag=true;
		for(int i=n;i>=1;i--){
			tree.Update(id[i],n,1,1,1,n);
			tree.Update(tmp[i],n,-1,1,1,n);
			if(tree.t[1].Min<0){flag=false;break;}
		}
		puts(flag?"AC":"WA");
	}
	return 0;
}