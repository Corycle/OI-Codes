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
using namespace std;
const ll inf=0x7f7f7f7f7f7f7f7f;
const ll N=2005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,tot,cnt,top,scc;
ll h[N],b[N],A[N],B[N];
ll p[N],st[N],dfn[N],low[N];
struct Point{ll x,y;}P1[N],P2[N];
struct edge{ll to,next;}d[N*N];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
ll Sqr(ll x){return x*x;}
ll Dist(Point A,Point B){
	return Sqr(A.x-B.x)+Sqr(A.y-B.y);
}
void Tarjan(ll x){
	dfn[x]=low[x]=++tot;
	st[++top]=x;p[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(p[y])low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		ll k=0;scc++;
		do{
			k=st[top--];
			b[k]=scc;p[k]=0;
		}while(k!=x);
	}
}
bool Check(ll x){
	cnt=tot=scc=0;
	memset(h,0,sizeof(h));
	memset(b,0,sizeof(b));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			if(i==j)continue;
			if(Dist(P1[i],P1[j])<x)Add(A[i],B[j]);
			if(Dist(P1[i],P2[j])<x)Add(A[i],A[j]);
			if(Dist(P2[i],P1[j])<x)Add(B[i],B[j]);
			if(Dist(P2[i],P2[j])<x)Add(B[i],A[j]);
		}
	}
	for(ll i=1;i<=n*2;i++){
		if(!dfn[i])Tarjan(i);
	}
	for(ll i=1;i<=n;i++){
		if(b[A[i]]==b[B[i]])return false;
	}
	return true;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		ll x=read(),y=read(),z=read();
		A[i]=++tot;P1[i]=(Point){x,y+z};
		B[i]=++tot;P2[i]=(Point){x,y-z};
	}
	ll l=0,r=inf,ans=0;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(Check(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%lld",ans);
	return 0;
}