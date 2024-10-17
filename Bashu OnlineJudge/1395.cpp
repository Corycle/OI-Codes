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
const ll inf=0x7f7f7f7f7f7f7f7f;
const ll N=50005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,root,tot,k,p[6],D;
struct KD{
	ll d[6],maxx[6],minn[6];
	ll ch[2];
}t[N];
priority_queue<Dist>q;
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
	if(l<mid)Build(t[rt].ch[0],l,mid-1,(d+1)%k);
	if(r>mid)Build(t[rt].ch[1],mid+1,r,(d+1)%k);
	Pushup(rt);
}
ll dist(ll x){
	ll ans=0;
	for(ll i=0;i<k;i++){
		ans+=(p[i]-t[x].d[i])*(p[i]-t[x].d[i]);
	}
	return ans;
}
ll Guess(ll x){
	ll ans=0;
	for(ll i=0;i<k;i++){
		if(p[i]<t[x].minn[i])ans+=(p[i]-t[x].minn[i])*(p[i]-t[x].minn[i]);
		if(p[i]>t[x].maxx[i])ans+=(p[i]-t[x].maxx[i])*(p[i]-t[x].maxx[i]);
	}
	return ans;
}
void Ask(ll x){
	if(x==0)return;
	ll dis=dist(x);
	ll dl=Guess(t[x].ch[0]);
	ll dr=Guess(t[x].ch[1]);
	if(dis<q.top().first){
		q.pop();
		q.push(make_pair(dis,x));
	}
	if(dl<dr){
		if(dl<q.top().first)Ask(t[x].ch[0]);
		if(dr<q.top().first)Ask(t[x].ch[1]);
	}
	else{
		if(dr<q.top().first)Ask(t[x].ch[1]);
		if(dl<q.top().first)Ask(t[x].ch[0]);
	}
}
void Print(){
	if(q.empty())return;
	ll x=q.top().second;
	q.pop();
	Print();
	for(ll i=0;i<k;i++)printf("%lld ",t[x].d[i]);
	printf("\n");
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(scanf("%lld%lld",&n,&k)!=EOF){
		memset(t,0,sizeof(t));
		while(q.size())q.pop();
		for(ll i=1;i<=n;i++){
			for(ll j=0;j<k;j++){
				t[i].d[j]=read();
			}
		}
		Build(root,1,n,0);
		ll T=read();
		while(T--){
			for(ll i=0;i<k;i++)p[i]=read();
			m=read();
			for(ll i=1;i<=m;i++){
				q.push(make_pair(inf,0));
			}
			Ask(root);
			printf("the closest %lld points are:\n",m);
			Print();
		}
	}
	return 0;
}