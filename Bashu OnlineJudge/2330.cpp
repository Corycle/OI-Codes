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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans[N*5];
int n,m,K,num;
int a[N],b[N],pos[N];
struct Tree{ll sum,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(ll x,int p,int l,int r){
		t[p].tag+=x;
		t[p].sum+=(r-l+1)*x;
	}
	void Pushdown(int p,int l,int r){
		if(t[p].tag){
			int mid=(l+r)>>1;
			update(t[p].tag,lson);
			update(t[p].tag,rson);
			t[p].tag=0;
		}
	}
	void Update(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(1,p,l,r);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Update(x,y,lson);Update(x,y,rson);
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	}
	ll Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p,l,r);
		return Query(x,y,lson)+Query(x,y,rson);
	}
}tree;
struct Ques{int l,r,id;};
vector<Ques>Q[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		Q[r].push_back((Ques){l,r,i});
	}
	b[0]=-1;
	for(int i=1;i<=n;i++){
		pos[++num]=i;b[num]=a[i];
		for(int j=1;j<=num;j++)b[j]&=a[i];
		int t=0;
		for(int j=1;j<=num;j++)if(b[j]!=b[j-1]){t++;b[t]=b[j];pos[t]=pos[j];}
		num=t;pos[num+1]=i+1;
		for(int j=1;j<=num;j++)if(b[j]%K==0)tree.Update(pos[j],pos[j+1]-1,1,1,n);
		for(auto tmp:Q[i])Ans[tmp.id]=tree.Query(tmp.l,tmp.r,1,1,n);
	}
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}