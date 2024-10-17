/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=2148473648ll;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll f[10],a[10];
ll mod(ll x){return x>=Mod?x-Mod:x;}
void DFS(ll x,ll tot,ll num){
	if(x>4){f[tot]=mod(f[tot]+num);return;}
	if(a[x]==1)DFS(x+1,tot+2,num);
	else{
		DFS(x+1,tot+1,mod(num+num));
		DFS(x+1,tot,num*(a[x]-2)%Mod);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();
	while(T--){
		memset(f,0,sizeof(f));
		for(ll i=1;i<=4;i++)a[i]=read();
		DFS(1,0,1);
		for(ll i=0;i<=8;i++)printf("%lld ",f[i]);
		printf("\n");
	}
	return 0;
}