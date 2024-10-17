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
const ll inf=0x3f3f3f3f;
const ll N=400005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,tot;
ll ans,ans1,ans2,rt[N];
struct Tree{
	ll l,r,data;
}t[N*20],tree[N];
void Update(ll &x,ll y,ll l,ll r){
	if(!x)x=++tot;
	t[x].data++;
	if(l==r)return;
	ll mid=(l+r)>>1;
	if(y<=mid)Update(t[x].l,y,l,mid);
	if(y>mid)Update(t[x].r,y,mid+1,r);
}
ll Merge(ll x,ll y){
	if(!x||!y)return x+y;
	t[x].data+=t[y].data;
	ans1+=t[t[x].l].data*t[t[y].r].data;
	ans2+=t[t[x].r].data*t[t[y].l].data;
	t[x].l=Merge(t[x].l,t[y].l);
	t[x].r=Merge(t[x].r,t[y].r);
	return x;
}
ll DFS(ll x){
	tree[x].data=read();
	if(tree[x].data){
		Update(rt[x],tree[x].data,1,n);
	}
	else{
		tree[x].l=DFS(++cnt);
		tree[x].r=DFS(++cnt);
		ans1=ans2=0;
		rt[x]=Merge(rt[tree[x].l],rt[tree[x].r]);
		ans+=min(ans1,ans2);
	}
	return x;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	DFS(++cnt);
	printf("%lld",ans);
	return 0;
}