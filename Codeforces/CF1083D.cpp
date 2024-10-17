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
const int Mod=1e9+7;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,top;
int a[N],b[N],st[N],num[N],lst[N],pre[N],nxt[N],fpre[N],fnxt[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Sum(int x){return (1ll*x*(x+1)/2)%Mod;}
int S(int l,int r){return mod(Sum(r)-Sum(l-1)+Mod);}
struct Tree{int sum[4],tag[2];};
struct Segment_Tree{
	Tree t[N*4];
	void update(int v,int type,int p,int l,int r){
		t[p].tag[type]=v;
		t[p].sum[type]=1ll*v*(r-l+1)%Mod;
		t[p].sum[2]=1ll*v*t[p].sum[type^1]%Mod;
		if(!type)t[p].sum[3]=1ll*v*S(l,r)%Mod;
	}
	void Pushdown(int p,int l,int r){
		int mid=(l+r)>>1;
		for(int i=0;i<2;i++){
			if(t[p].tag[i]){
				update(t[p].tag[i],i,lson);
				update(t[p].tag[i],i,rson);
				t[p].tag[i]=0;
			}
		}
	}
	void Pushup(int p){for(int i=0;i<4;i++)t[p].sum[i]=mod(t[p<<1].sum[i]+t[p<<1|1].sum[i]);}
	void Update(int x,int y,int v,int type,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(v,type,p,l,r);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Update(x,y,v,type,lson);Update(x,y,v,type,rson);Pushup(p);
	}
	int Query(int x,int y,int type,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum[type];
		int mid=(l+r)>>1;Pushdown(p,l,r);
		return mod(Query(x,y,type,lson)+Query(x,y,type,rson));
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+n+1);b[0]=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+b[0]+1,a[i])-b;
	for(int i=1;i<=n;i++){pre[i]=lst[a[i]]+1;lst[a[i]]=i;}
	for(int i=1;i<=b[0];i++)lst[i]=n+1;
	for(int i=n;i>=1;i--){nxt[i]=lst[a[i]]-1;lst[a[i]]=i;}
	top=0;for(int i=n;i>=1;i--){while(top&&pre[i]>pre[st[top]])top--;fpre[i]=(top?st[top]-1:n);st[++top]=i;}
	top=0;for(int i=n;i>=1;i--){while(top&&nxt[i]<nxt[st[top]])top--;fnxt[i]=(top?st[top]-1:n);st[++top]=i;}
	for(int i=n,j=n;i>=1;i--){
		tree.Update(i,fpre[i],pre[i],0,1,1,n);
		tree.Update(i,fnxt[i],nxt[i],1,1,1,n);
		num[a[i]]++;while(num[a[i]]>1){num[a[j]]--;j--;}
		Ans=mod(Ans+1ll*tree.Query(i,j,1,1,1,n)*i%Mod);
		Ans=mod(Ans-tree.Query(i,j,2,1,1,n)+Mod);
		Ans=mod(Ans+tree.Query(i,j,3,1,1,n));
		Ans=mod(Ans-1ll*S(i,j)*i%Mod+Mod);
	}
	printf("%d",Ans);
	return 0;
}
