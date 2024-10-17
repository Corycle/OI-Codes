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
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,top;
int a[N],st[N],Min[N],Max[N];
struct Tree{int tag,sum;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int l,int r){
		t[p].tag=1;t[p].sum=r-l+1;
	}
	void Pushdown(int p,int l,int r){
		if(t[p].tag){
			int mid=(l+r)>>1;
			update(lson);update(rson);
		}
	}
	void Pushup(int p){
		t[p].tag=t[p<<1].tag&t[p<<1|1].tag;
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	}
	void Build(int p,int l,int r){
		t[p].tag=t[p].sum=0;
		if(l==r)return;
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
	}
	void Update(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,l,r);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Update(x,y,lson);Update(x,y,rson);
		Pushup(p);
	}
	int Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p,l,r);
		return Ask(x,y,lson)+Ask(x,y,rson);
	}
}tree;
void Prepare(){
	top=Ans=0;
	tree.Build(1,1,n);
	for(int i=1;i<=n;i++)Max[i]=0;
	for(int i=1;i<=n;i++)Min[i]=inf;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();Prepare();
		for(int i=1;i<=n;i++){
			a[i]=read();
			Max[a[i]]=max(Max[a[i]],i);
			Min[a[i]]=min(Min[a[i]],i);
		}
		for(int i=1;i<=n;i++){
			st[++top]=i;
			while(top&&Max[a[st[top]]]<=i)top--;
			if(i==Max[a[i]]&&i!=Min[a[i]]){
				tree.Update(Min[a[i]]+1,Max[a[i]],1,1,n);
			}
			int pos=top?st[top]+1:1;
			Ans+=(i-pos+1)-tree.Ask(pos,i,1,1,n);
		}
		printf("%lld\n",Ans);
	}
	return 0;
}