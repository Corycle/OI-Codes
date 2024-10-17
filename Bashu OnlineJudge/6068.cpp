#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<stack>
#include<queue>
#include<map>
#include<vector>
#include<cstring>
#define ll long long
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,a[100005],ans;
int main(){
//	freopen("road.in","r",stdin);
//	freopen("road.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		a[i]=read();
		if(a[i]>a[i-1]){
			ans+=a[i]-a[i-1];
		}
	}
	printf("%lld",ans);
	return 0;
}
