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
const ll N=25;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll c[N],f[N][N][N];
ll DFS(ll x,ll y,ll sum,ll flag,ll num){
	// 深度 前导零  
	if(!x)return sum;
	if(!flag&&f[x][y][sum]!=-1)return f[x][y][sum];
	ll k=flag?c[x]:9,s=0;
	for(ll i=0;i<=k;i++){
		s+=DFS(x-1,y||i,sum+((y||i)&&(i==num)),flag&&i==k,num);
	}
	if(!flag)f[x][y][sum]=s;
	return s;
}
ll Ask(ll x,ll y){
	c[0]=0;
	while(x){
		c[++c[0]]=x%10;
		x/=10;
	}
	return DFS(c[0],0,0,1,y);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll a=read(),b=read();
	for(ll i=0;i<=9;i++){
		memset(f,-1,sizeof(f));
		printf("%lld ",Ask(b,i)-Ask(a-1,i));
	}
	return 0;
}