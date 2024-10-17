#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
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
const ll inf=123456789123456789ll;
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll k[N],b[N];
ll n,m,cnt,tot,Lim,total;
ll sum[N],top[N],son[N],dis[N];
ll h[N],fa[N],id[N],dep[N],pos[N];
struct edge{ll to,next,data;}d[N*2];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct Segment_Tree{//李超线段树 区修区查 
	struct Tree{ll num;ll Min;}t[N*4];
	ll GetY(ll x,ll num){
		return num?k[num]*x+b[num]:inf;
	}
	void Pushup(ll p,ll l,ll r){
		t[p].Min=min(GetY(dis[pos[l]],t[p].num),GetY(dis[pos[r]],t[p].num));
		if(l!=r)t[p].Min=min(t[p].Min,min(t[p<<1].Min,t[p<<1|1].Min));
	}
	void Build(ll p,ll l,ll r){
		t[p].Min=inf;
		if(l==r)return;
		ll mid=(l+r)>>1;
		Build(lson);Build(rson);
	}
	void Update(ll x,ll y,ll num,ll p,ll l,ll r){
		if(y<l||x>r)return;
		ll mid=(l+r)>>1;
		if(x<=l&&r<=y){
			ll lx=dis[pos[l]],rx=dis[pos[r]],midx=dis[pos[mid]];
			if(GetY(lx,num)>=GetY(lx,t[p].num)&&GetY(rx,num)>=GetY(rx,t[p].num))return;
			if(GetY(lx,num)<=GetY(lx,t[p].num)&&GetY(rx,num)<=GetY(rx,t[p].num)){
				t[p].num=num;Pushup(p,l,r);return;
			}
			if(k[num]<k[t[p].num]){
				if(GetY(midx,num)<GetY(midx,t[p].num)){
					Update(x,y,t[p].num,lson);t[p].num=num;
				}
				else Update(x,y,num,rson);
			}
			else{
				if(GetY(midx,num)<GetY(midx,t[p].num)){
					Update(x,y,t[p].num,rson);t[p].num=num;
				}
				else Update(x,y,num,lson);
			}
			Pushup(p,l,r);
			return;
		}
		Update(x,y,num,lson);
		Update(x,y,num,rson);
		Pushup(p,l,r);
	}
	ll Ask(ll x,ll y,ll p,ll l,ll r){
		if(y<l||x>r)return inf;
		if(x<=l&&r<=y)return t[p].Min;
		ll mid=(l+r)>>1;
		ll ans=min(Ask(x,y,lson),Ask(x,y,rson));
		ans=min(ans,GetY(dis[pos[max(x,l)]],t[p].num));
		ans=min(ans,GetY(dis[pos[min(y,r)]],t[p].num));
		return ans;
	}
}Tree;
//以下为树剖 
void DFS1(ll x,ll depth){
	sum[x]=1;dep[x]=depth;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;
		dis[y]=dis[x]+d[i].data;
		DFS1(y,depth+1);
		sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(ll x,ll tp){
	top[x]=tp;
	id[x]=++tot;pos[tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
ll lca(ll x,ll y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])return x;
	return y;
}
void Update(ll x,ll y,ll K,ll B){
	total++;
	k[total]=K;b[total]=B;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		Tree.Update(id[top[x]],id[x],total,1,1,Lim);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	Tree.Update(id[x],id[y],total,1,1,Lim);
}
ll Ask(ll x,ll y){
	ll ans=inf;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=min(ans,Tree.Ask(id[top[x]],id[x],1,1,Lim));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans=min(ans,Tree.Ask(id[x],id[y],1,1,Lim));
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=2;i<=n;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	Lim=m<<1;
	DFS1(1,1);DFS2(1,1);
	Tree.Build(1,1,Lim);
	while(m--){
		ll op=read();
		if(op==1){
			ll x=read(),y=read();
			ll K=read(),B=read();
			ll z=lca(x,y);
			Update(x,z,-K,dis[x]*K+B);
			Update(y,z,K,(dis[x]-dis[z]*2)*K+B);
		}
		if(op==2){	
			ll x=read(),y=read();
			printf("%lld\n",Ask(x,y));
		}
	}
	return 0;
}