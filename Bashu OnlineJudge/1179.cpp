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
const ll inf=1e10;
const ll N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll c[N],f[N][N][2];
ll DFS(ll x,ll y,ll z,ll flag){
	if(!x)return z;
	if(!flag&&f[x][y][z]!=-1)return f[x][y][z];
	ll k=flag?c[x]:9,s=0;
	for(ll i=0;i<=k;i++){
		if(i==6)s+=DFS(x-1,y+1,z||y+1>=3,flag&&i==k);
		else s+=DFS(x-1,0,z,flag&&i==k);
	}
	if(!flag)f[x][y][z]=s;
	return s;
}
ll Ask(ll x){
	c[0]=0;
	while(x){
		c[++c[0]]=x%10;
		x/=10;
	}
	return DFS(c[0],0,0,1);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	memset(f,-1,sizeof(f));
	ll T=read();
	while(T--){
		ll x=read();
		ll l=0,r=inf,ans=0;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(Ask(mid)>=x){
				ans=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}