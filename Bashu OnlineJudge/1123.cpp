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
const int inf=0x3f3f3f3f;
const int N=25;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll c[N],f[N][N][N][N];
ll DFS(ll x,ll y,ll z1,ll z2,ll flag){
	if(!x)return z2&&!y;
	if(!flag&&f[x][y][z1][z2]!=-1)return f[x][y][z1][z2];
	ll k=flag?c[x]:9,s=0;
	for(int i=0;i<=k;i++){
		s+=DFS(x-1,(y*10+i)%13,i,z2||(z1==1&&i==3),flag&&i==k);
	}
	if(!flag)f[x][y][z1][z2]=s;
	return s;
}
ll Ask(ll x){
	c[0]=0;
	while(x){
		c[++c[0]]=x%10;
		x/=10;
	}
	return DFS(c[0],0,0,0,1);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll x=0;
	memset(f,-1,sizeof(f));
	while(scanf("%lld",&x)!=EOF){
		printf("%lld\n",Ask(x));
	}
	return 0;
}