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
const ll N=100005;
const ll M=31;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,lst,tmp1,tmp2;
struct Node{
	int tot,a[N],sum[N][M];
	void Insert(ll x){
		x^=tmp1;a[++tot]=x;
		for(ll i=0;i<=30;i++){
			sum[tot][i]=sum[tot-1][i]+((x>>i)&1);
		}
	}
	ll Query(ll x){
		ll ans=0;
		if(!x)return 0;
		for(ll i=0;i<=30;i++){
			if(((tmp1>>i)&1)==0)ans+=(1ll<<i)*sum[x][i];
			if(((tmp1>>i)&1)==1)ans+=(1ll<<i)*(x-sum[x][i]);
		}
		return ans;
	}
}F;
struct Trie{
	int tot=1,ch[N*M][2],sum[N*M][M],Size[N*M];
	void Insert(ll x){
		ll p=1;
		for(ll i=30;i>=0;i--){
			ll c=(x>>i)&1;
			if(!ch[p][c])ch[p][c]=++tot;
			p=ch[p][c];Size[p]++;
			for(ll j=0;j<=30;j++){
				if((x>>j)&1)sum[p][j]++;
			}
		}
	}
	ll Query(ll x){
		ll ans=0,p=1;
		if(!x)return 0;
		for(ll i=30;i>=0;i--){
			ll l=0,r=1;
			if((tmp2>>i)&1)swap(l,r);
			if(x<=Size[ch[p][l]])p=ch[p][l];
			else{
				for(ll j=0;j<=30;j++){
					if(((tmp1>>j)&1)==0)ans+=(1ll<<j)*sum[ch[p][l]][j];
					if(((tmp1>>j)&1)==1)ans+=(1ll<<j)*(Size[ch[p][l]]-sum[ch[p][l]][j]);
				}
				x-=Size[ch[p][l]];p=ch[p][r];
			}
		}
		for(ll i=0;i<=30;i++){
			if(((tmp1>>i)&1)==0)ans+=(1ll<<i)*(sum[p][i]?x:0);
			if(((tmp1>>i)&1)==1)ans+=(1ll<<i)*(sum[p][i]?0:x);
		}
		return ans;
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++)F.Insert(read());
	m=read();
	while(m--){
		ll op=read();
		if(op==1)F.Insert(read());
		if(op==2){
			ll l=read(),r=read(),ans=0;
			if(l>lst&&r>lst)ans=F.Query(r-lst)-F.Query(l-lst-1);
			if(l<=lst&&r<=lst)ans=tree.Query(r)-tree.Query(l-1);
			if(l<=lst&&r>lst)ans=tree.Query(lst)-tree.Query(l-1)+F.Query(r-lst);
			printf("%lld\n",ans);
		}
		if(op==3)tmp1^=read();
		if(op==4){
			for(ll i=1;i<=F.tot;i++)tree.Insert(F.a[i]);
			lst+=F.tot;tmp2=tmp1;F.tot=0;
		}
	}
	return 0;
}