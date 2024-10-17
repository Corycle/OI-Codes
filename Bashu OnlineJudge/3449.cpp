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
const ll inf=9e18;
const ll N=4e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,tot,Ans,b[N],f[N];
struct Node{ll sx,sy,tx,ty;}P[N];
struct Operation{ll op,y,id;};
vector<Operation>F[N];
bool cmp1(Node A,Node B){return A.sx!=B.sx?A.sx<B.sx:A.sy<B.sy;}
bool cmp2(Operation A,Operation B){return A.y!=B.y?A.y<B.y:A.op<B.op;}
struct BIT{
	ll c[N];
	ll lowbit(ll x){return x&(-x);}
	void Init(){for(ll i=1;i<=tot;i++)c[i]=inf;}
	void Add(ll x,ll y){for(ll i=x;i<=tot;i+=lowbit(i))c[i]=min(c[i],y);}
	ll Ask(ll x){ll ans=inf;for(ll i=x;i>=1;i-=lowbit(i))ans=min(ans,c[i]);return ans;}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	b[++tot]=0;b[++tot]=n;
	for(ll i=1;i<=m;i++){
		b[++tot]=P[i].sx=read();
		b[++tot]=P[i].sy=read();
		b[++tot]=P[i].tx=read();
		b[++tot]=P[i].ty=read();
	}
	sort(b+1,b+tot+1);
	sort(P+1,P+m+1,cmp1);
	tot=unique(b+1,b+tot+1)-b-1;
	for(ll i=1;i<=m;i++){
		ll sx=lower_bound(b+1,b+tot+1,P[i].sx)-b;
		ll sy=lower_bound(b+1,b+tot+1,P[i].sy)-b;
		ll tx=lower_bound(b+1,b+tot+1,P[i].tx)-b;
		ll ty=lower_bound(b+1,b+tot+1,P[i].ty)-b;
		F[sx].push_back((Operation){1,sy,i});
		F[tx].push_back((Operation){0,ty,i});
		f[i]=inf;
	}
	tree.Init();
	tree.Add(1,n+n);
	for(ll i=1;i<=tot;i++){
		sort(F[i].begin(),F[i].end(),cmp2);
		for(auto t:F[i]){
			if(t.op==0){
				ll dlt=(n-P[t.id].tx)+(n-P[t.id].ty);
				tree.Add(t.y,f[t.id]+dlt);
			}
			if(t.op==1){
				ll dlt=(n-P[t.id].sx)+(n-P[t.id].sy);
				f[t.id]=tree.Ask(t.y)-dlt;
			}
		}
	}
	printf("%lld",tree.Ask(tot));
	return 0;
}