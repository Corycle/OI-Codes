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
const ll N=205;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll f[25][N][N];
int c[N],v[25][N][N],mod;
ll DFS(int x,int y,int z,int flag){
	if(y>mod||y+x*9<mod)return 0;
	if(!x)return y==mod&&!z;
	if(!flag&&v[x][y][z]==mod)return f[x][y][z];
	ll k=flag?c[x]:9,s=0;
	for(register int i=0;i<=k;i++){
		s+=DFS(x-1,y+i,(z*10+i)%mod,flag&&i==k);
	}
	if(!flag){
		f[x][y][z]=s;
		v[x][y][z]=mod;
	}
	return s;
}
ll Ask(ll x){
	c[0]=0;
	while(x){
		c[++c[0]]=x%10;
		x/=10;
	}
	ll sum=0;
	for(register int i=c[0]*9;i>=1;i--){
		mod=i;
		sum+=DFS(c[0],0,0,1);
	}
	return sum;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll a=read(),b=read();
	printf("%lld",Ask(b)-Ask(a-1));
	return 0;
}