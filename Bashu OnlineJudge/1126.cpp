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
const ll M=N*N;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll p[N],c[N],f[N][M],Max;
ll F(ll x){
	ll ans=0,cnt=0;
	while(x){
		ans+=(x%10)*p[cnt++];
		x/=10;
	}
	return ans;
}
ll DFS(ll x,ll y,ll flag){
	if(y>Max)return 0;
	if(!x)return y<=Max;
	if(!flag&&f[x][y]!=-1)return f[x][y];
	ll k=flag?c[x]:9,s=0;
	for(ll i=0;i<=k;i++){
		s+=DFS(x-1,y+p[x-1]*i,flag&&i==k);
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
	p[0]=1;
	for(ll i=1;i<=10;i++)p[i]=p[i-1]*2;
	ll T=read();
	for(ll Case=1;Case<=T;Case++){
		memset(f,-1,sizeof(f));
		ll a=read(),b=read();Max=F(a);
		printf("Case #%lld: %lld\n",Case,Ask(b));
	}
	return 0;
}