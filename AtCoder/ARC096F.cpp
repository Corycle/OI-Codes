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
const ll M=200005;
const ll N=55;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<ll>G[N];
ll n,m,d,Ans,f[M],fa[N];
struct Node{
	ll a,b,id;
	friend bool operator<(Node A,Node B){return A.a*B.b<A.b*B.a;}
}P[N];
void DFS(ll x){for(auto y:G[x]){DFS(y);P[x].a+=P[y].a;P[x].b+=P[y].b;}}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();d=read();
	P[1].a=read();P[1].b=1;P[1].id=1;
	for(ll i=2;i<=n;i++){
		P[i].a=read();P[i].b=1;P[i].id=i;
		G[fa[i]=read()].push_back(i);
	}
	DFS(1);
	memset(f,0x3f,sizeof(f));
	ll Max=n*n*n,L=min(n,d);f[0]=0;
	for(ll i=1;i<=n;i++){
		ll x=L;
		for(ll j=0;(1<<j)<=x;j++){
			x-=(1<<j);
			ll val=P[i].a*(1<<j),num=P[i].b*(1<<j);
			for(ll k=Max;k>=num;k--)f[k]=min(f[k],f[k-num]+val);
		}
		if(x){
			ll val=P[i].a*x,num=P[i].b*x;
			for(ll k=Max;k>=num;k--)f[k]=min(f[k],f[k-num]+val);
		}
	}
	sort(P+1,P+n+1);
	while(P[n].id!=1)n--;
	for(ll i=0;i<=Max;i++){
		if(f[i]>m)continue;
		ll num=i,val=f[i];
		for(ll j=1;j<n;j++){
			ll tmp=min(d-L,(m-val)/P[j].a);
			val+=P[j].a*tmp;num+=P[j].b*tmp;
		}
		ll tmp=(m-val)/P[n].a;
		val+=P[n].a*tmp;num+=P[n].b*tmp;
		Ans=max(Ans,num);
	}
	printf("%lld",Ans);
	return 0;
}
