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
const ll N=1000005;
const ll M=305;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<ll>d[M];
ll n,m,f[N],g[N],s[N];
struct Node{ll c,v;}P[N];
bool cmp(Node A,Node B){
	if(A.c==B.c)return A.v>B.v;
	return A.c<B.c;
}
void Solve(ll ql,ll qr,ll l,ll r,ll t){
	if(l>r)return;
	ll mid=(l+r)>>1;
	ll id=0,tmp=0,Max=0;
	for(ll i=ql;i<=qr;i++){
		if(i<mid){
			tmp=g[d[t][i]]+s[mid-i];
			if(tmp>Max){Max=tmp;id=i;}
		}
	}
	f[d[t][mid]]=max(f[d[t][mid]],Max);
	Solve(ql,id,l,mid-1,t);
	Solve(id,qr,mid+1,r,t);
}
int main(){
//	freopen("jewelry.in","r",stdin);
//	freopen("jewelry.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		P[i].c=read();
		P[i].v=read();
	}
	sort(P+1,P+n+1,cmp);
	memset(s,-0x3f,sizeof(s));
	for(ll i=1;i<=n;i++){
		ll l=i,r=i;s[0]=0;
		while(P[r+1].c==P[i].c)r++;
		for(ll j=0;j<=m;j++)g[j]=f[j];
		for(ll j=r-l+2;j<=m;j++)s[j]=-inf;
		for(ll j=l;j<=r;j++)s[j-i+1]=s[j-i]+P[j].v;
		for(ll j=0;j<=m;j++)d[j%P[i].c].push_back(j);
		for(ll j=0;j<P[i].c;j++){
			if(!d[j].size())continue;
			ll num=d[j].size()-1;
			Solve(0,num,0,num,j);
			d[j].clear();
		}
		i=r;
	}
	for(ll i=1;i<=m;i++)printf("%lld ",f[i]);
	return 0;
}