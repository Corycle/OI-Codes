/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=200;
const ll M=20;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int c[M];
ll f[M][N][N];
ll DFS(int x,int Max,int sum,int p,int flag){
	if(!x)return (Max==sum&&p==0);
	if(!flag&&f[x][sum][p]!=-1)return f[x][sum][p];
	int k=(flag?c[x]:9);ll ans=0;
	for(int i=0;i<=k;i++){
		if(sum+i>Max)break;
		ans+=DFS(x-1,Max,sum+i,(p*10+i)%Max,flag&(i==k));
	}
	if(!flag&&f[x][sum][p]==-1)f[x][sum][p]=ans;
	return ans;
}
ll Ask(ll n){
	c[0]=0;
	while(n){
		c[++c[0]]=n%10;
		n/=10;
	}
	ll ans=0;
	for(ll i=1;i<=c[0]*9;i++){
		memset(f,-1,sizeof(f));
		ans+=DFS(c[0],i,0,0,1);
	}
	return ans;
}
int main(){
//	freopen("number.in","r",stdin);
//	freopen("number.out","w",stdout);
	ll n=read();
	printf("%lld",Ask(n));
	return 0;
}