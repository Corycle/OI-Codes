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
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,V,top,st[N];
struct Node{ll x,T,a,b;}P[N];
bool cmp(Node A,Node B){return A.b!=B.b?A.b<B.b:A.a<B.a;}
void Solve(ll type){
	st[top=0]=-inf;
	for(ll i=1;i<=n;i++){
		if(type==1&&P[i].T*V<abs(P[i].x))continue;
		if(st[top]<=P[i].a)st[++top]=P[i].a;
		else st[upper_bound(st+1,st+top+1,P[i].a)-st]=P[i].a;
	}
	printf("%lld ",top);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		P[i].x=read();
		P[i].T=read();
	}
	V=read();
	for(ll i=1;i<=n;i++){
		P[i].a=P[i].T*V+P[i].x;
		P[i].b=P[i].T*V-P[i].x;
	}
	sort(P+1,P+n+1,cmp);
	Solve(1);Solve(2);
	return 0;
}