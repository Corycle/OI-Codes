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
const ll N=5005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,Ans,pos[N],vis[N];
struct Node{ll s,t,v,pos;}a[N];
bool cmp1(Node x,Node y){return x.s<y.s;}
bool cmp2(Node x,Node y){return x.v>y.v;}
bool Check(ll x,ll p){
	if(pos[p]>a[x].t)return false;
	if(!vis[p]){vis[p]=x;return true;}
	else{
		if(a[vis[p]].t<a[x].t)return Check(x,p+1);
		else if(Check(vis[p],p+1)){vis[p]=x;return true;}
		return false;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		a[i].s=read();
		a[i].t=read();
		a[i].v=read();
	}
	sort(a+1,a+n+1,cmp1);
	for(ll i=1;i<=n;i++)pos[i]=max(pos[i-1]+1,a[i].s);
	for(ll i=1;i<=n;i++)a[i].pos=lower_bound(pos+1,pos+n+1,a[i].s)-pos;
	sort(a+1,a+n+1,cmp2);
	for(ll i=1;i<=n;i++){
		if(Check(i,a[i].pos))Ans+=a[i].v;
	}
	printf("%lld",Ans);
	return 0;
}