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
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,root,top,a[N],st[N],num[N],tot[N];
struct tree{
	ll l,r,fa;
	ll dis;
}t[N];
ll Merge(ll x,ll y){
	if(!x||!y)return x+y;
	if(a[x]<a[y])swap(x,y);
	t[x].r=Merge(t[x].r,y);
	if(t[t[x].l].dis<t[t[x].r].dis)swap(t[x].l,t[x].r);
	if(!t[x].r)t[x].dis=0;
	else t[x].dis=t[t[x].r].dis+1;
	return x;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		a[i]=read();
		top++;
		st[top]=i;
		num[top]=1;//左偏树中元素数 
		tot[top]=1;//区间中元素个数 
		while(top>1){
			if(a[st[top-1]]<=a[st[top]])break;
			num[top-1]+=num[top];
			tot[top-1]+=tot[top];
			st[top-1]=Merge(st[top-1],st[top]);
			top--;
			while(num[top]*2>tot[top]+1){//删除堆顶元素 
				st[top]=Merge(t[st[top]].l,t[st[top]].r);
				num[top]--;
			}
		}
	}
	ll cnt=1,ans=0;
	for(ll i=1;i<=top;i++){
		for(ll j=cnt;j<=cnt+tot[i]-1;j++){
			ans+=abs(a[j]-a[st[i]]);
		}
		cnt+=tot[i];
	}
	printf("%lld",ans);
	return 0;
}
