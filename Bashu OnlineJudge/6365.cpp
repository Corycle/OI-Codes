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
const ll inf=0x3f3f3f3f;
const ll Mod=1e9+7;
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll n,m,K;
ll a[N],b[N],p1[N],p2[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(){
	p1[0]=1;
	for(ll i=1;i<=n;i++)a[i]=(s[i]-'a'+1)%Mod;
	for(ll i=1;i<=n;i++)p1[i]=p1[i-1]*K%Mod;
	for(ll i=1;i<=n;i++)p2[i]=(p2[i-1]+p1[i])%Mod;
}
struct Tree{ll Ans,sum,len,lsum,rsum;}Ans;
Tree Merge(Tree A,Tree B){
	Tree P;
	P.len=(A.len+B.len)%Mod;
	P.sum=(A.sum*p1[B.len]%Mod+B.sum)%Mod;
	P.lsum=(A.lsum+B.lsum+A.sum*p2[B.len]%Mod)%Mod;
	P.rsum=(B.rsum+A.rsum*p1[B.len]%Mod+B.sum*A.len%Mod)%Mod;
	P.Ans=(A.Ans+B.Ans+A.rsum*p2[B.len]%Mod+B.lsum*A.len%Mod)%Mod;
	return P;
}
struct Segment_Tree{
	Tree t[N*4];
	void update(ll p,ll x){
		t[p].Ans=t[p].sum=t[p].lsum=t[p].rsum=x;
	}
	void Build(ll p,ll l,ll r){
		t[p].len=r-l+1;
		if(l==r){update(p,a[l]);return;}
		ll mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p]=Merge(t[p<<1],t[p<<1|1]);
	}
	void Change(ll x,ll p,ll l,ll r){
		if(x<l||x>r)return;
		if(l==r){update(p,a[l]);return;}
		ll mid=(l+r)>>1;
		Change(x,lson);Change(x,rson);
		t[p]=Merge(t[p<<1],t[p<<1|1]);
	}
	void Query(ll x,ll y,ll p,ll l,ll r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			if(!Ans.len)Ans=t[p];
			else Ans=Merge(Ans,t[p]);
			return;
		}
		ll mid=(l+r)>>1;
		Query(x,y,lson);Query(x,y,rson);
	}
}tree;
int main(){
//	freopen("letter.in","r",stdin);
//	freopen("letter.out","w",stdout);
	n=read();m=read();K=read();
	scanf("%s",s+1);Prepare();
	tree.Build(1,1,n);
	char ch[5];
	while(m--){
		ll op=read();
		if(op==0){
			ll l=read(),r=read();
			ll len=(r-l+1);
			Ans={0,0,0,0,0};
			tree.Query(l,r,1,1,n);
			len=(1+len)*len/2%Mod;
			printf("%lld\n",Ans.Ans*Pow(len,Mod-2)%Mod);
		}
		if(op==1){
			ll x=read();
			scanf("%s",ch);
			a[x]=ch[0]-'a'+1;
			tree.Change(x,1,1,n);
		}
	}
	return 0;
}