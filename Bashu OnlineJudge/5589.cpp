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
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
queue<ll>q[N];
ll n,m,cnt,Ans,total;
ll tot=1,lst=1,root=1;
ll a[N],h[N],fa[N],rt[N];
ll pos[N],len[N],ch[N][30];
struct Tree{ll ch[2];}t[N*50];
struct edge{ll to,next;}d[N];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Insert(ll x,ll p){
	for(ll i=20;i>=0;i--){
		ll c=(x>>i)&1;
		if(!t[p].ch[c])t[p].ch[c]=++total;
		p=t[p].ch[c];
	}
}
ll Ask(ll x,ll p){
	ll ans=0;
	for(ll i=20;i>=0;i--){
		ll c=(x>>i)&1;
		if(t[p].ch[c^1]){
			ans+=(1ll<<i);
			p=t[p].ch[c^1];
		}
		else p=t[p].ch[c];
	}
	return ans;
}
void SAM(ll num){
	ll x=lst,fx=++tot;len[fx]=len[x]+1;
	while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
	if(!x)fa[fx]=root;
	else{
		ll y=ch[x][num];
		if(len[y]==len[x]+1)fa[fx]=y;
		else{
			ll fy=++tot;len[fy]=len[x]+1;
			for(ll i=1;i<=26;i++)ch[fy][i]=ch[y][i];
			fa[fy]=fa[y];fa[y]=fa[fx]=fy;
			while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
		}
	}
	lst=fx;
}
ll Merge(ll x,ll y,ll addv){
	if(!q[x].size())return y;
	if(!q[y].size())return x;
	if(q[x].size()<q[y].size())swap(x,y);
	while(q[y].size()){
		Ans=max(Ans,Ask(q[y].front(),x)+addv);
		Insert(q[y].front(),x);
		q[x].push(q[y].front());
		q[y].pop();
	}
	return x;
}
void DFS(ll x){
	if(pos[x]){
		Insert(a[pos[x]],rt[x]);
		q[rt[x]].push(a[pos[x]]);
	}
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;DFS(y);
		rt[x]=Merge(rt[x],rt[y],len[x]);
	}
}
int main(){
//	freopen("xt.in","r",stdin);
//	freopen("xt.out","w",stdout);
	n=read();scanf("%s",s+1);
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=n;i>=1;i--){SAM(s[i]-'a'+1);pos[lst]=i;}
	for(ll i=1;i<=tot;i++){rt[i]=++total;Add(fa[i],i);}
	DFS(root);
	printf("%lld",Ans);
	return 0;
}