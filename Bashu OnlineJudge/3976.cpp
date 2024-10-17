/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
#define pii pair<ll,ll>
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=2147483648ll;
const ll N=100005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline ll read(){
	ll s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
pii b[N];
ll n,m,cnt;
ll g[N],c[N],mu[N],Ans[N],vis[N],prime[N];
struct ques{ll n,m,a,id;}q[N];
bool cmp(ques x,ques y){
	return x.a<y.a;
}
ll lowbit(ll x){return x&(-x);}
ll Add(ll x,ll y){
	for(ll i=x;i<=m;i+=lowbit(i)){
		c[i]=(c[i]+y)%Mod;
	}
}
ll Ask(ll x){
	ll ans=0;
	for(ll i=x;i>=1;i-=lowbit(i)){
		ans=(ans+c[i])%Mod;
	}
	return ans;
}
void Prepare(){
	mu[1]=1;
	for(ll i=2;i<=m;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(ll j=1;j<=cnt&&i*prime[j]<=m;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
	for(ll i=1;i<=m;i++){
		for(ll j=1;i*j<=m;j++)g[i*j]+=i;
		b[i].first=g[i];b[i].second=i;
	}
	sort(b+1,b+m+1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		q[i].id=i;q[i].n=read();q[i].m=read();q[i].a=read();
		if(q[i].n>q[i].m)swap(q[i].n,q[i].m);m=max(m,q[i].m);
	}
	ll k=1;Prepare();
	sort(q+1,q+n+1,cmp);
	for(ll i=1;i<=n;i++){
		while(k<=m&&b[k].first<=q[i].a){
			for(ll j=1;j*b[k].second<=m;j++){
				Add(j*b[k].second,(b[k].first*mu[j]+Mod)%Mod);
			}
			k++;
		}
		for(ll l=1,r;l<=q[i].n;l=r+1){
			r=min(q[i].n/(q[i].n/l),q[i].m/(q[i].m/l));
			Ans[q[i].id]=(Ans[q[i].id]+(q[i].n/l)%Mod*(q[i].m/l)%Mod*(Ask(r)-Ask(l-1)+Mod)%Mod)%Mod;
		}
	}
	for(ll i=1;i<=n;i++)printf("%lld\n",Ans[i]);
	return 0;
}