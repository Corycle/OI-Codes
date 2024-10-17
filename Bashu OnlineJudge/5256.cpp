#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=5000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
ll v[N],a[N],b[N];
void DFS(ll l,ll r,ll sum,ll c[]){
	if(sum>m)return;
	if(l==r+1){c[++c[0]]=sum;return;}
	DFS(l+1,r,sum+v[l],c);
	DFS(l+1,r,sum,c);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)v[i]=read();
	ll mid=n/2,ans=0;
	DFS(1,mid,0,a);
	DFS(mid+1,n,0,b);
	sort(a+1,a+a[0]+1);
	for(ll i=1;i<=b[0];i++){
		ans+=upper_bound(a+1,a+a[0]+1,m-b[i])-a-1;
	}
	printf("%lld",ans);
	return 0;
}