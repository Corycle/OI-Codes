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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
#define Dist pair<ll,ll>
//Dist 前为估计距离，后为下标 
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,root,tot,k=2,p[3],D;
struct KD{
	ll d[3],maxx[3],minn[3];
	ll ch[2];
}t[N];
priority_queue<Dist,vector<Dist>,greater<Dist> >q;
bool cmp(KD x,KD y){
	return x.d[D]<y.d[D];
}
void Pushup(ll x){
	ll l=t[x].ch[0],r=t[x].ch[1];
	for(ll i=0;i<k;i++){
		if(l){
			t[x].maxx[i]=max(t[x].maxx[i],t[l].maxx[i]);
			t[x].minn[i]=min(t[x].minn[i],t[l].minn[i]);
		}
		if(r){
			t[x].maxx[i]=max(t[x].maxx[i],t[r].maxx[i]);
			t[x].minn[i]=min(t[x].minn[i],t[r].minn[i]);
		}
	}
}
void Build(ll &rt,ll l,ll r,ll d){//d为当前建立的层的分辨器 
	ll mid=(l+r)>>1;
	D=d;rt=mid;
	nth_element(t+l,t+mid,t+r+1,cmp);
	for(ll i=0;i<k;i++){
		t[rt].maxx[i]=t[rt].minn[i]=t[rt].d[i];
	}
	if(l<mid)Build(t[rt].ch[0],l,mid-1,d^1);
	if(r>mid)Build(t[rt].ch[1],mid+1,r,d^1);
	Pushup(rt);
}
ll pw(ll x){
	return x*x;
}
ll dist(ll x){
	return pw(p[0]-t[x].d[0])+pw(p[1]-t[x].d[1]);
}
ll Guess(ll x){
	ll ans=0;
	for(ll i=0;i<k;i++){
		ans+=max(pw(p[i]-t[x].maxx[i]),pw(p[i]-t[x].minn[i]));
	}
	return ans;
}
void Ask(ll x){
	if(x==0)return;
	ll dis=dist(x);
	if(dis>q.top().first){
		q.pop();
		q.push(make_pair(dis,x));
	}
	ll dl=Guess(t[x].ch[0]);
	ll dr=Guess(t[x].ch[1]);
	if(dl>dr){
		if(dl>q.top().first)Ask(t[x].ch[0]);
		if(dr>q.top().first)Ask(t[x].ch[1]);
	}
	else{
		if(dr>q.top().first)Ask(t[x].ch[1]);
		if(dl>q.top().first)Ask(t[x].ch[0]);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll n=read();m=read()*2;
	for(ll i=1;i<=n;i++){
		t[i].d[0]=read();
		t[i].d[1]=read();
	}
	Build(root,1,n,0);
	for(ll i=1;i<=m;i++){
		q.push(make_pair(-inf,0));
	}
	for(ll i=1;i<=n;i++){
		p[0]=t[i].d[0];
		p[1]=t[i].d[1];
		Ask(root);
	}
	printf("%lld",q.top().first);
	return 0;
}