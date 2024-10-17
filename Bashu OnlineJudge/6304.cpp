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
const ll inf=9e18;
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<ll>G[N];
ll n,Sum,Ans=inf;
ll a[N],fa[N],f1[N],f2[N],sum1[N],sum2[N];
bool cmp(ll x,ll y){
	return sum1[x]*sum2[y]<sum1[y]*sum2[x];
}
void DFS1(ll x){
	ll num=G[x].size();
	sum1[x]=1;sum2[x]=a[x];
	for(ll i=0;i<num;i++){
		ll y=G[x][i];
		if(y==fa[x])continue;
		fa[y]=x;DFS1(y);
		sum1[x]+=sum1[y];
		sum2[x]+=sum2[y];
	}
	f1[x]=a[x];Sum+=a[x];
	sort(G[x].begin(),G[x].end(),cmp);
	for(ll i=0,p=1;i<num;i++){
		ll y=G[x][i];
		if(y==fa[x])continue;
		f1[x]+=f1[y]+sum2[y]*p;
		p+=sum1[y];
	}
}
void DFS2(ll x){
	ll num=G[x].size();
	if(fa[x]){
		f1[fa[x]]=f2[x];
		sum1[fa[x]]=n-sum1[x];
		sum2[fa[x]]=Sum-sum2[x];
	}
	f1[x]=a[x];
	sort(G[x].begin(),G[x].end(),cmp);
	for(ll i=0,p=1;i<num;i++){
		ll y=G[x][i];
		f1[x]+=f1[y]+sum2[y]*p;
		p+=sum1[y];
	}
	Ans=min(Ans,f1[x]);
	for(ll i=0,p=1,dlt=a[x];i<num;i++){
		ll y=G[x][i];dlt+=sum2[y];
		if(y==fa[x]){p+=sum1[y];continue;}
		f2[y]=f1[x]-(f1[y]+sum2[y]*p)-sum1[y]*(Sum-dlt);
		p+=sum1[y];
	}
	for(ll i=0;i<num;i++){
		ll y=G[x][i];
		if(y!=fa[x])DFS2(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(ll i=1;i<=n;i++)a[i]=read();
	DFS1(1);DFS2(1);
	printf("%lld",Ans);
	return 0;
}