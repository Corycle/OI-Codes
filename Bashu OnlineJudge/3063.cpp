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
const ll N=300005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans,n,c[N],a[N];
struct Node{ll x,y;}car[N];
bool cmp(Node a,Node b){return a.x<b.x;}
void Solve(ll l,ll r){
	if(l+1<r){
		ll mid=(l+r)/2,id=l,i,j;
		Solve(l,mid-1);Solve(mid,r);
		for(i=l,j=mid;(i<=mid-1)&&(j<=r);){
			if(a[i]>a[j]){
				c[id++]=a[j++];
				Ans+=mid-i;
			}
			else c[id++]=a[i++];
		}
		if(j<=r) for(j;j<=r;j++,id++)c[id]=a[j];
		else for(j;i<=mid-1;i++,id++)c[id]=a[i];
		for(ll i=l;i<=r;i++)a[i]=c[i];
	}
	else{
		if(l+1==r&&a[l]>a[r]){
			swap(a[l],a[r]);Ans++;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		car[i].x=read();
		car[i].y=read();
	}
	sort(car+1,car+1+n,cmp);
	for(ll i=1;i<=n;i++)a[i]=car[i].y;
	Solve(1,n);
	printf("%lld",Ans);
	return 0;
}