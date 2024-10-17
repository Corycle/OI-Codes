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
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,cnt,Min,tot,Ans;
ll h[N],F[N],C[N],D[N],A[N],val[N],vis[N],Max1[N],Max2[N];
struct edge{ll to,next;}d[N];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(ll x){
	if(vis[x]==tot){Ans-=Min;return;}
	if(vis[x])return;vis[x]=tot;
	Min=min(Min,val[Max1[x]]-val[Max2[x]]);
	if(Max1[x]!=x)DFS(Max1[x]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		F[i]=read();C[i]=read();
		D[i]=read();A[i]=read();
		Add(F[i],i);
	}
	for(ll i=1;i<=n;i++){
		val[i]=D[F[i]]-C[i];
		if(val[i]<=0)continue;
		if(val[i]>val[Max1[F[i]]]){
			Max2[F[i]]=Max1[F[i]];
			Max1[F[i]]=i;
		}
		else if(val[i]>val[Max2[F[i]]])Max2[F[i]]=i;
	}
	for(ll i=1;i<=n;i++)Ans+=val[Max1[i]]*A[i];
	for(ll i=1;i<=n;i++)if(!vis[i]){tot++;Min=inf;DFS(i);}
	printf("%lld",Ans);
	return 0;
}