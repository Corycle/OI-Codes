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
const ll Maxn=1e4;
const ll N=50005;
const ll M=65;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,c,tot,Mod;
ll h[N][M],Pow1[N][M],Pow2[N][M];
ll a[N][M],d[N],sum[N],num[N],Phi[N];
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%mod;
		tot=tot*tot%mod;
		y>>=1;
	}
	return ans;
}
ll KSM(ll x,ll y,ll &flag){
	ll ans=1,tot=x;flag=0;
	while(y){
		if(y&1)ans=ans*tot;
		tot=tot*tot;
		if(tot>1e8){
			flag=1;
			break;
		}
		y>>=1;
	}
	return flag?inf:ans;
}
ll GetPhi(ll x){
	ll phi=x;
	for(ll i=2;i*i<=x;i++){
		if(x%i==0){
			phi=phi/i*(i-1);
			while(x%i==0)x/=i;
		}
	}
	if(x!=1)phi=phi/x*(x-1);
	return phi;
}
ll Pow(ll y,ll k){
	return Pow1[y%Maxn][k]*Pow2[y/Maxn][k]%Phi[k];
}
ll Calc(ll pos,ll P,ll k){
	if(k>=tot)return 0;
	if(k==P)return a[pos][0]%Phi[k];
	if(c==1)return Pow(Calc(pos,P,k+1),k);
	ll phi=Phi[k+1];
	if(c!=1&&P-k-1<=num[pos]&&P-k-1>=0&&h[pos][P-k-1]<phi)
		return Pow(Calc(pos,P,k+1),k);
	else return Pow(Calc(pos,P,k+1)+phi,k);
}
void Prepare(){
	Phi[0]=Mod;
	while(1){
		tot++;
		Phi[tot]=GetPhi(Phi[tot-1]);
		if(Phi[tot]==1&&Phi[tot-1]==1)break;
	}
	for(ll i=0;i<=tot;i++){
		ll tmp=Pow(c,Maxn,Phi[i]);
		for(ll j=0;j<=Maxn;j++)Pow1[j][i]=Pow(c,j,Phi[i]);
		for(ll j=0;j<=Maxn;j++)Pow2[j][i]=Pow(tmp,j,Phi[i]);
	}
}
struct Segment_Tree{
	struct Tree{ll sum,Min;}t[N*4];
	void Pushup(ll p){
		t[p].Min=min(t[p<<1].Min,t[p<<1|1].Min);
		t[p].sum=(t[p<<1].sum+t[p<<1|1].sum)%Mod;
	}
	void Build(ll p,ll l,ll r){
		if(l==r){t[p].sum=a[l][0];return;}
		ll mid=(l+r)>>1;
		Build(lson);Build(rson);Pushup(p);
	}
	void Update(ll x,ll y,ll p,ll l,ll r){
		if(y<l||x>r||t[p].Min>=tot)return;
		if(l==r){
			t[p].Min++;
			t[p].sum=a[l][++d[l]];
			return;
		}
		ll mid=(l+r)>>1;
		Update(x,y,lson);Update(x,y,rson);
		Pushup(p);
	}
	ll Ask(ll x,ll y,ll p,ll l,ll r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		ll mid=(l+r)>>1;
		return (Ask(x,y,lson)+Ask(x,y,rson))%Mod;
	}
}tree;
int main(){
//	freopen("verbinden.in","r",stdin);
//	freopen("verbinden.out","w",stdout);
	n=read();m=read();
	Mod=read();c=read();
	Prepare();
	for(ll i=1;i<=n;i++)a[i][0]=read();
	for(ll i=1;i<=n;i++){
		h[i][0]=a[i][0];ll flag=0;
		for(num[i]=1;num[i]<=tot;num[i]++){
			h[i][num[i]]=KSM(c,h[i][num[i]-1],flag);
			if(flag)break;
		}
		num[i]--;
		for(ll j=1;j<=tot;j++)a[i][j]=Calc(i,j,0)%Mod;
	}
	tree.Build(1,1,n);
	while(m--){
		ll op=read(),l=read(),r=read();
		if(op==0)tree.Update(l,r,1,1,n);
		if(op==1)printf("%lld\n",tree.Ask(l,r,1,1,n)%Mod);
	}
	return 0;
}