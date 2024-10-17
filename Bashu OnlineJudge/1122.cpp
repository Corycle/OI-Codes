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
ll K,B,c[N],f[N][N];
ll DFS(ll x,ll y,ll flag){
	if(y>K)return 0;
	if(!x)return y==K;
	if(!flag&&f[x][y]!=-1)return f[x][y];
	ll s=0;
	if(!flag||c[x])s+=DFS(x-1,y+1,flag&&c[x]==1);
	s+=DFS(x-1,y,flag&&!c[x]);
	if(!flag)f[x][y]=s;
	return s;
}
ll Ask(ll x){
	c[0]=0;
	while(x){
		c[++c[0]]=x%B;
		x/=B;
	}
	return DFS(c[0],0,1);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll x=read(),y=read();
	K=read(),B=read();
	memset(f,-1,sizeof(f));
	printf("%lld\n",Ask(y)-Ask(x-1));
	return 0;
}