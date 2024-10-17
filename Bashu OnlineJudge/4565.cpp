#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
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
ll n1,n2,ans,c[N];
struct node{
	ll x,id;
}a[N];
bool cmp(node x,node y){
	return x.x>y.x;
}
ll lowbit(ll x){
	return x&(-x);
}
void Add(ll x,ll y){
	for(ll i=x;i<=n1+n2;i+=lowbit(i)){
		c[i]+=y;
	}
}
ll Ask(ll x){
	ll tmp=0;
	for(ll i=x;i>=1;i-=lowbit(i)){
		tmp+=c[i];
	}
	return tmp;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n1=read(),n2=read();
	for(ll i=n1;i>=1;i--){
		Add(i,1);
		a[i].id=i;
		a[i].x=read();
	}
	for(ll i=n1+1;i<=n1+n2;i++){
		Add(i,1);
		a[i].id=i;
		a[i].x=read();
	}
	sort(a+1,a+n1+n2+1,cmp);
	ll p=n1;
	for(ll i=1;i<=n1+n2;i++){
		if(p<a[i].id){
			ans+=Ask(a[i].id-1)-Ask(p);
			p=a[i].id-1;
			Add(a[i].id,-1);
		}
		else{
			ans+=Ask(p)-Ask(a[i].id);
			p=a[i].id;
			Add(a[i].id,-1);
		}
	}
	printf("%lld",ans);
	return 0;
}
