/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=1e9+7;
const ll N=50005;
const ll M=11;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,a[N],C[N][M];
struct Segment_Tree{
	struct Tree{
		ll a[M],tag,rev,len;
		void Init(){
			tag=rev=len=0;
			memset(a,0,sizeof(a));
		}
	}t[N*4];
	void Reverse(ll p){
		t[p].rev^=1;
		for(ll i=1;i<=9;i+=2){
			t[p].a[i]=(Mod-t[p].a[i])%Mod;
		}
	}
	void Update(ll p,ll c){
		ll f[M]={0},len=t[p].len;c=(c%Mod+Mod)%Mod;
		if(t[p].rev==1)t[p].tag=(t[p].tag-c+Mod)%Mod;
		if(t[p].rev==0)t[p].tag=(t[p].tag+c+Mod)%Mod;
		f[0]=1;for(ll i=1;i<M;i++)f[i]=f[i-1]*c%Mod;
		for(ll i=10;i>=1;i--){
			for(ll j=0;j<i;j++){
				t[p].a[i]=(t[p].a[i]+t[p].a[j]*f[i-j]%Mod*C[len-j][i-j]%Mod+Mod)%Mod;
			}
		}
	}
	void Pushdown(ll p){
		if(t[p].tag){
			Update(p<<1,t[p].tag);
			Update(p<<1|1,t[p].tag);
			t[p].tag=0;
		}
		if(t[p].rev){
			t[p].rev^=1;
			Reverse(p<<1);
			Reverse(p<<1|1);
		}
	}
	Tree Merge(Tree l,Tree r){
		Tree p;p.Init();
		p.len=l.len+r.len;p.a[0]=1;
		for(ll i=1;i<=10;i++){
			for(ll j=0;j<=i;j++){
				p.a[i]+=l.a[j]*r.a[i-j]%Mod;
			}
			p.a[i]=(p.a[i]%Mod+Mod)%Mod;
		}
		return p;
	}
	void Build(ll p,ll l,ll r){
		if(l==r){
			t[p].len=1;
			t[p].a[0]=1;
			t[p].a[1]=a[l];
			return;
		}
		ll mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p]=Merge(t[p<<1],t[p<<1|1]);
	}
	void Add(ll x,ll y,ll z,ll p,ll l,ll r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Update(p,z);return;}
		ll mid=(l+r)>>1;Pushdown(p);
		Add(x,y,z,lson);Add(x,y,z,rson);
		t[p]=Merge(t[p<<1],t[p<<1|1]);
	}
	void Rev(ll x,ll y,ll p,ll l,ll r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Reverse(p);return;}
		ll mid=(l+r)>>1;Pushdown(p);
		Rev(x,y,lson);Rev(x,y,rson);
		t[p]=Merge(t[p<<1],t[p<<1|1]);
	}
	Tree Ask(ll x,ll y,ll p,ll l,ll r){
		if(x<=l&&r<=y)return t[p];
		ll mid=(l+r)>>1;Pushdown(p);
		if(y<=mid)return Ask(x,y,lson);
		if(x>mid) return Ask(x,y,rson);
		return Merge(Ask(x,y,lson),Ask(x,y,rson));
	}
}tree;
void Prepare(){
	C[0][0]=1;
	for(ll i=1;i<=n;i++){
		C[i][0]=1;
		for(ll j=1;j<M;j++){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare();
	for(ll i=1;i<=n;i++){
		a[i]=(read()%Mod+Mod)%Mod;
	}
	tree.Build(1,1,n);
	while(m--){
		ll op=read(),a=read(),b=read();
		if(op==1)tree.Add(a,b,read(),1,1,n);
		if(op==2)tree.Rev(a,b,1,1,n);
		if(op==3)printf("%lld\n",(tree.Ask(a,b,1,1,n).a[read()]%Mod+Mod)%Mod);
	}
	return 0;
}