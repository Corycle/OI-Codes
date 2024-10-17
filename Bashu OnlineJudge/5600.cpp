#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,step;
ll c[N],h[N],st[N],ed[N],pos[N];
struct edge{ll to,next;}d[N*2];
struct Node{ll l,r,q;};
vector<ll>v1[N];
vector<Node>v2[N];
bool operator<(Node A,Node B){
	return A.q>B.q;
}
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(ll x){
	pos[st[x]=++step]=x;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(!st[y])DFS(y);
	}
	ed[x]=step;
}
void Add(ll sx,ll tx,ll sy,ll ty){
	if(sx>tx||sy>ty)return;
	if(sx>sy){swap(sx,sy);swap(tx,ty);}
	v2[sx].push_back((Node){sy,ty,-1});
	v2[tx+1].push_back((Node){sy,ty,1});
}
void Solve(ll x,ll y){
	if(st[x]>st[y])swap(x,y);
	if(st[x]<st[y]&&st[y]<=ed[x]){
		for(ll i=h[x];i;i=d[i].next){
			ll fy=d[i].to;
			if(st[fy]<=st[y]&&st[y]<=ed[fy]){
				Add(1,st[fy]-1,st[y],ed[y]);
				Add(ed[fy]+1,n,st[y],ed[y]);
			}
		}
	}
	else Add(st[x],ed[x],st[y],ed[y]);
}
struct Segment_Tree{
	struct Tree{ll l,r,sum,tag;}t[N*4];
	void Pushup(ll p){
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	}
	void Build(ll p,ll l,ll r){
		if(l==r){t[p].sum=1;return;}
		ll mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	}
	ll Ask(ll x,ll y,ll p,ll l,ll r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		ll mid=(l+r)>>1;
		return Ask(x,y,lson)+Ask(x,y,rson);
	}
	void Update(ll x,ll y,ll z,ll p,ll l,ll r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			t[p].tag+=z;
			if(t[p].tag<0)t[p].sum=0;
			else if(l==r)t[p].sum=1;
			else Pushup(p);
			return;
		}
		ll mid=(l+r)>>1;
		Update(x,y,z,lson);
		Update(x,y,z,rson);
		if(!t[p].tag)Pushup(p);
	}
}tree;
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		c[i]=read();
		v1[c[i]].push_back(i);
	}
	for(ll i=2;i<=n;i++){
		ll x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1);
	for(ll i=1;i<=n;i++){//对于每两点，构造矩形并更新扫描线 
		ll num=v1[i].size();
		for(ll j=0;j<num;j++){
			for(ll k=j+1;k<num;k++){
				Solve(v1[i][j],v1[i][k]);
			}
		}
	}
	ll Ans=0;
	tree.Build(1,1,n);
	for(ll i=1;i<=n;i++){
		ll num=v2[i].size();
		sort(v2[i].begin(),v2[i].end());
		for(ll j=0;j<num;j++){
			Node x=v2[i][j];
			tree.Update(x.l,x.r,x.q,1,1,n);
		}
		Ans+=tree.Ask(i,n,1,1,n);
	}
	printf("%lld",Ans);
	return 0;
}