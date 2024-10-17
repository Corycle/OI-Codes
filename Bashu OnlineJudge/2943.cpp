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
const ll N=500005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,Ans;
double Sum;
ll b1[N],b2[N];
struct Point{ll x,y,id;}t[N];
bool cmp1(Point A,Point B){return A.id<B.id;}
bool cmp2(Point A,Point B){return A.x<B.x;}
struct Node{ll ans;double sum;}f1[N],f2[N];
struct BIT{
	Node c[N];
	ll lowbit(ll x){return x&(-x);}
	void Init(ll x){for(;x<=n;x+=lowbit(x))c[x]=(Node){0,0};}
	void Add(ll x,ll ans,double sum){
		for(;x<=n;x+=lowbit(x)){
			if(c[x].ans==ans)c[x].sum+=sum;
			if(c[x].ans<ans){c[x].ans=ans;c[x].sum=sum;}
		}
	}
	Node Ask(ll x){
		ll ans=0;double sum=0;
		for(;x>=1;x-=lowbit(x)){
			if(c[x].ans==ans)sum+=c[x].sum;
			if(c[x].ans>ans){ans=c[x].ans;sum=c[x].sum;}
		}
		return (Node){ans,sum};
	}
}tree;
void CDQ1(ll l,ll r){
	if(l==r)return;
	ll mid=(l+r)>>1;
	sort(t+l,t+r+1,cmp1);
	CDQ1(l,mid);
	sort(t+l,t+mid+1,cmp2);
	sort(t+mid+1,t+r+1,cmp2);
	ll p1=l,p2=mid+1;
	while(p2<=r){
		if(p1<=mid&&t[p1].x<=t[p2].x){
			tree.Add(t[p1].y,f1[t[p1].id].ans+1,f1[t[p1].id].sum);
			p1++;
		}
		else{
			Node dlt=tree.Ask(t[p2].y);
			if(f1[t[p2].id].ans==dlt.ans)f1[t[p2].id].sum+=dlt.sum;
			if(f1[t[p2].id].ans<dlt.ans)f1[t[p2].id]=dlt;
			p2++;
		}
	}
	for(ll i=l;i<=mid;i++)tree.Init(t[i].y);
	sort(t+l,t+r+1,cmp1);
	CDQ1(mid+1,r);
}
void CDQ2(ll l,ll r){
	if(l==r)return;
	ll mid=(l+r)>>1;
	sort(t+l,t+r+1,cmp1);
	CDQ2(mid+1,r);
	sort(t+l,t+mid+1,cmp2);
	sort(t+mid+1,t+r+1,cmp2);
	ll p2=l,p1=mid+1;
	while(p2<=mid){
		if(p1<=r&&t[p1].x<=t[p2].x){
			tree.Add(t[p1].y,f2[t[p1].id].ans+1,f2[t[p1].id].sum);
			p1++;
		}
		else{
			Node dlt=tree.Ask(t[p2].y);
			if(f2[t[p2].id].ans==dlt.ans)f2[t[p2].id].sum+=dlt.sum;
			if(f2[t[p2].id].ans<dlt.ans)f2[t[p2].id]=dlt;
			p2++;
		}
	}
	for(ll i=mid+1;i<=r;i++)tree.Init(t[i].y);
	sort(t+l,t+r+1,cmp1);
	CDQ2(l,mid);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		t[i].id=i;
		t[i].x=b1[++b1[0]]=read();
		t[i].y=b2[++b2[0]]=read();
	}
	sort(b1+1,b1+b1[0]+1);b1[0]=unique(b1+1,b1+b1[0]+1)-b1-1;
	sort(b2+1,b2+b2[0]+1);b2[0]=unique(b2+1,b2+b2[0]+1)-b2-1;
	for(ll i=1;i<=n;i++){
		t[i].x=lower_bound(b1+1,b1+b1[0]+1,t[i].x)-b1;
		t[i].y=lower_bound(b2+1,b2+b2[0]+1,t[i].y)-b2;
	}
	for(ll i=1;i<=n;i++){
		f1[i]=(Node){1,1};
		f2[i]=(Node){1,1};
		t[i].x=b1[0]-t[i].x+1;
		t[i].y=b2[0]-t[i].y+1;
	}
	CDQ1(1,n);
	for(ll i=1;i<=n;i++){
		t[i].x=b1[0]-t[i].x+1;
		t[i].y=b2[0]-t[i].y+1;
	}
	CDQ2(1,n);
	for(ll i=1;i<=n;i++)Ans=max(Ans,f1[i].ans);
	for(ll i=1;i<=n;i++)if(Ans==f1[i].ans)Sum+=f1[i].sum;
	printf("%lld\n",Ans);
	for(ll i=1;i<=n;i++){
		ll ans=f1[i].ans+f2[i].ans-1;
		double sum=f1[i].sum*f2[i].sum;
		if(ans!=Ans)printf("%.5lf ",0.0);
		else printf("%.5lf ",sum/Sum);
	}
	return 0;
}