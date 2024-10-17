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
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=2e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,Root[N];
struct Tree{ll l,r,sum;};
struct Segment_Tree{
	Tree t[N*40];
	ll st[N*40],top,tot;
	ll NewNode(){return top?st[top--]:++tot;}
	void Delete(ll p){t[p].l=t[p].r=t[p].sum=0;st[++top]=p;}
	void Insert(ll x,ll num,ll &p,ll l,ll r){
		if(!p)p=NewNode();t[p].sum+=num;
		if(l==r)return;ll mid=(l+r)>>1;
		x<=mid?Insert(x,num,lson):Insert(x,num,rson);
	}
	ll Query(ll x,ll y,ll p,ll l,ll r){
		if(y<l||x>r||!p)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		ll mid=(l+r)>>1;
		return Query(x,y,lson)+Query(x,y,rson);
	}
	ll Kth(ll k,ll p,ll l,ll r){
		if(l==r)return l;ll mid=(l+r)>>1;
		if(t[t[p].l].sum>=k)return Kth(k,lson);
		return Kth(k-t[t[p].l].sum,rson);
	}
	void Split(ll x,ll &y,ll k){
		if(!x)return;y=NewNode();
		if(k>t[t[x].l].sum)Split(t[x].r,t[y].r,k-t[t[x].l].sum);
		else{t[y].r=t[x].r;t[x].r=0;}
		if(k<t[t[x].l].sum)Split(t[x].l,t[y].l,k);
		t[y].sum=t[x].sum-k;t[x].sum=k;
	}
	ll Merge(ll x,ll y){
		if(!x||!y)return x|y;
		t[x].sum+=t[y].sum;
		t[x].l=Merge(t[x].l,t[y].l);
		t[x].r=Merge(t[x].r,t[y].r);
		Delete(y);
		return x;
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();cnt=1;
	for(ll i=1;i<=n;i++)tree.Insert(i,read(),Root[1],1,n);
	while(m--){
		ll op=read();
		if(op==0){
			ll id=read(),x=read(),y=read();
			ll k1=tree.Query(1,y,Root[id],1,n);
			ll k2=tree.Query(x,y,Root[id],1,n);
			ll tmp=0;cnt++;
			tree.Split(Root[id],Root[cnt],k1-k2);
			tree.Split(Root[cnt],tmp,k2);
			Root[id]=tree.Merge(Root[id],tmp);
		}
		if(op==1){ll x=read(),y=read();Root[x]=tree.Merge(Root[x],Root[y]);}
		if(op==2){ll id=read(),y=read(),x=read();tree.Insert(x,y,Root[id],1,n);}
		if(op==3){ll id=read(),x=read(),y=read();printf("%lld\n",tree.Query(x,y,Root[id],1,n));}
		if(op==4){ll x=read(),k=read();printf("%lld\n",tree.t[Root[x]].sum<k?-1:tree.Kth(k,Root[x],1,n));}
	}
	return 0;
}