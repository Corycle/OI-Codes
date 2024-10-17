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
const ll N=2005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,cnt;
ll h[N],val[N],f[N][5];
struct edge{ll to,next;}d[N];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(ll x){
	bool flag=false;
	ll sum1=0,sum2=0,sum3=val[x],ans=inf;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;DFS(y);
		ans=min(ans,f[y][2]-f[y][0]);
		if(f[y][2]>f[y][0])sum1+=f[y][0];
		else{flag=true;sum1+=f[y][2];}  
		sum2+=f[y][0];
		sum3+=min(f[y][0],min(f[y][1],f[y][2]));
	}
	if(!flag)sum1+=ans;
	f[x][0]=sum1;
	f[x][1]=sum2;
	f[x][2]=sum3;
}
bool vis[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","val",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		ll x=read();
		val[x]=read();
		ll num=read();
		while(num--){
			ll y=read();
			Add(x,y);
			vis[y]=1;  
		}
	}
	ll s=0;
	for(ll i=1;i<=n;i++){
		if(!vis[i]){s=i;break;}
	}
	DFS(s);
	printf("%lld\n",min(f[s][0],f[s][2]));  
	return 0;
}