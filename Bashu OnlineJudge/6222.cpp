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
const ll inf=0x7f7f7f7f7f7f7f7f;
const ll M=1000005;
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,c[M];
vector<ll>V1[N],V2[N*4];
struct Node{ll x,y,f;}a[N];
ll Calc(Node A,Node B){return A.f+(B.x-A.x)*(B.y-A.y);}
bool cmp(Node A,Node B){return A.x!=B.x?A.x<B.x:A.y<B.y;}

ll lowbit(ll x){return x&(-x);}
ll Add(ll x,ll y){for(ll i=x;i<=m+1;i+=lowbit(i))c[i]=max(c[i],y);}
ll Ask(ll x){ll ans=0;for(ll i=x;i>=1;i-=lowbit(i))ans=max(ans,c[i]);return ans;}

struct Segment_Tree{
	ll top,st[N*4],flag[N*4];
	void Init(){
		while(top){
			V2[st[top]].clear();
			flag[st[top--]]=0;
		}
	}
	void Push(ll p,ll x){
		V2[p].push_back(x);
		if(!flag[p]){flag[p]=1;st[++top]=p;}
	}
	void Update(ll l,ll r,ll ql,ll qr,vector<ll>&v1,vector<ll>&v2){
		if(l>r)return;//用v2更新v1 
		ll mid=(l+r)>>1,Min=inf,pos=-1;
		for(ll i=ql;i<=qr;i++){
			ll k=Calc(a[v2[i]],a[v1[mid]]);
			if(k<Min){Min=k;pos=i;}
		}
		a[v1[mid]].f=min(a[v1[mid]].f,Min);
		Update(l,mid-1,pos,qr,v1,v2);
		Update(mid+1,r,ql,pos,v1,v2);
	}
	void Change(ll p,ll l,ll r,ll x,vector<ll>&V){
		if(a[V[r]].y>a[x].y||a[V[l]].x>a[x].x)return;
		if(a[V[l]].y<=a[x].y&&a[V[r]].x<=a[x].x){Push(p,x);return;}
		ll mid=(l+r)>>1;Change(lson,x,V);Change(rson,x,V);
	}
	void Solve(ll p,ll l,ll r,vector<ll>&V){
		if(V2[p].size())Update(0,V2[p].size()-1,l,r,V2[p],V);
		if(l==r)return;ll mid=(l+r)>>1;
		Solve(lson,V);Solve(rson,V);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		ll x=read(),y=read();
		a[i]=(Node){x,y,inf};
	}
	sort(a+1,a+n+1,cmp);
	ll Max=0;
	for(ll i=1;i<=n;i++){
		ll k=Ask(a[i].y+1)+1;
		V1[k].push_back(i);
		Max=max(Max,k);
		Add(a[i].y+1,k);
	}
	ll num=V1[1].size();
	for(ll i=0;i<num;i++){
		a[V1[1][i]].f=Calc((Node){0,0,0},a[V1[1][i]]);
	}
	for(ll i=2;i<=Max;i++){
		ll num1=V1[i].size();
		ll num2=V1[i-1].size();
		for(ll j=0;j<num1;j++){
			tree.Change(1,0,num2-1,V1[i][j],V1[i-1]);
		}
		tree.Solve(1,0,num2-1,V1[i-1]);
		tree.Init();
	}
	ll Ans=inf;
	num=V1[Max].size();
	for(ll i=0;i<num;i++){
		Ans=min(Ans,Calc(a[V1[Max][i]],(Node){m,m,0}));
	}
	printf("%lld",Ans);
	return 0;
}