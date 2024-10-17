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
ll c[N],f[N][N][N];
ll DFS(ll x,ll y,ll z,ll flag){
	if(!x)return z;
	if(!flag&&f[x][y][z]!=-1)return f[x][y][z];
	ll k=flag?c[x]:9,s=0;
	for(ll i=0;i<=k;i++){
		s+=DFS(x-1,i,z||(y==4&&i==9),flag&&i==k);
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
	ll Case=read();
	while(Case--){
		ll x=read();
		printf("%lld\n",Ask(x));
	}
	return 0;
}