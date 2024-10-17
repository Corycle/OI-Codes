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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,ans[N],c[N],a[N];
struct node{
	ll type,x,y,data;
}t[N*10],tmp[N*10];
ll lowbit(ll x){
	return x&(-x);
}
void Add(ll x,ll y){
	for(ll i=x;i<=n;i+=lowbit(i)){
		c[i]+=y;
	}
}
ll Ask(ll x){
	ll tot=0;
	for(ll i=x;i>=1;i-=lowbit(i)){
		tot+=c[i];
	}
	return tot;
}
bool cmp(node x,node y){
	if(x.x!=y.x)return x.x<y.x;
	if(x.y!=y.y)return x.y<y.y;
	return x.type<y.type;
}
void CDQ(ll l,ll r){
	if(l==r)return;
	ll mid=(l+r)>>1;
	CDQ(l,mid);
	CDQ(mid+1,r);
	ll i=l,j=mid+1;
	for(ll k=l;k<=r;k++){
		if(j>r||i<=mid&&cmp(t[i],t[j])){
			if(t[i].type==1)Add(t[i].y,t[i].data);
			tmp[k]=t[i++];
		}
		else{
			if(t[j].type==2)ans[t[j].data]+=Ask(t[j].y);
			if(t[j].type==3)ans[t[j].data]-=Ask(t[j].y);
			tmp[k]=t[j++];
		}
	}
	for(ll k=l;k<=mid;k++){
		if(t[k].type==1)Add(t[k].y,-t[k].data);
	}
	for(ll k=l;k<=r;k++){
		t[k]=tmp[k];
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	ll cnt=0,qnt=0;
	qnt++;
	for(ll i=1;i<=n;i++){
		ll x=read();
		a[x]=i;
		t[++cnt]=(node){1,i,x,1};
		t[++cnt]=(node){2,i-1,n,qnt};
		t[++cnt]=(node){3,i-1,x,qnt};
		t[++cnt]=(node){2,n,x-1,qnt};
		t[++cnt]=(node){3,i,x-1,qnt};
	}
	for(ll i=1;i<=m;i++){
		ll x=read();
		qnt++;
		ll p=a[x];
		t[++cnt]=(node){1,p,x,-1};
		t[++cnt]=(node){2,p-1,n,qnt};
		t[++cnt]=(node){3,p-1,x,qnt};
		t[++cnt]=(node){2,n,x-1,qnt};
		t[++cnt]=(node){3,p,x-1,qnt};
	}
	CDQ(1,cnt);
	for(ll i=1;i<=m;i++){
		printf("%lld\n",ans[i]);
		ans[i+1]=ans[i]-ans[i+1];
	}
	return 0;
}