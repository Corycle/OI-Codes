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
const ll N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll c[N],f[N][N];
ll DFS(ll x,ll y,ll flag){
	if(!x)return 1;
	if(!flag&&f[x][y]!=EOF)return f[x][y];
	ll k=flag?c[x]:9,s=0;
	for(ll i=y;i<=k;i++){
		s+=DFS(x-1,i,flag&&i==k);
	}
	if(!flag)f[x][y]=s;
	return s;
}
ll Ask(ll x){
	c[0]=0;
	while(x){
		c[++c[0]]=x%10;
		x/=10;
	}
	return DFS(c[0],0,1);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll a,b;
	memset(f,-1,sizeof(f));
	while(scanf("%lld%lld",&a,&b)!=EOF){
		printf("%lld\n",Ask(b)-Ask(a-1));
	}
	return 0;
}