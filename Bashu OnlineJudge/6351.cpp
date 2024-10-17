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
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
ll a[N],Ans1[N],Ans2[N],Ans3[N];
map<ll,ll>F12[N],F13[N],F23[N];
struct Node{
	ll fa[N],sum[N];
	ll Find(ll x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
	void Init(){for(ll i=1;i<=n;i++){fa[i]=i;sum[i]=a[i];}}
	void Union(ll x,ll y){x=Find(x);y=Find(y);if(x!=y){fa[x]=y;sum[y]+=sum[x];}}
}F1,F2,F3;
int main(){
//	freopen("grape.in","r",stdin);
//	freopen("grape.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	F1.Init();F2.Init();F3.Init();
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read(),z=read();
		if(z!=1)F1.Union(x,y);
		if(z!=2)F2.Union(x,y);
		if(z!=3)F3.Union(x,y);
	}
	for(ll i=1;i<=n;i++){
		ll id1=F1.Find(i);
		ll id2=F2.Find(i);
		ll id3=F3.Find(i);
		F12[id1][id2]+=a[i];
		F13[id1][id3]+=a[i];
		F23[id2][id3]+=a[i];
	}
	for(ll i=1;i<=n;i++){
		ll id1=F1.Find(i);
		ll id2=F2.Find(i);
		ll id3=F3.Find(i);
		ll Ans12=F1.sum[id1]+F2.sum[id2]-F12[id1][id2];
		ll Ans13=F1.sum[id1]+F3.sum[id3]-F13[id1][id3];
		ll Ans23=F2.sum[id2]+F3.sum[id3]-F23[id2][id3];
		Ans1[id1]=max(Ans1[id1],max(Ans12,Ans13));
		Ans2[id2]=max(Ans2[id2],max(Ans12,Ans23));
		Ans3[id3]=max(Ans3[id3],max(Ans13,Ans23));
	}
	ll T=read();
	while(T--){
		ll x=read(),Ans=0;
		Ans=max(Ans,Ans1[F1.Find(x)]);
		Ans=max(Ans,Ans2[F2.Find(x)]);
		Ans=max(Ans,Ans3[F3.Find(x)]);
		printf("%lld\n",Ans);
	}
	return 0;
}