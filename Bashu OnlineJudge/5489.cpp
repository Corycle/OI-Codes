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
const ll N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<ll,ll>F;
ll n,K,tot,a[N];
void DFS(ll x){
	if(F[x])return;
	for(ll i=2;i<=60;i++){
		ll tmp=(1ll<<i)-1;
		if(x%tmp==0){
			DFS(x/tmp);
			if(F[x/tmp]!=-1){
				F[x]=i;
				return;
			}
		}
	}
	F[x]=-1;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	K=read();
	while(!(K&1)){tot++;K/=2;}
	n+=tot+2;F[1]=1;DFS(K);
	if(F[K]==-1){printf("qnq");return 0;}
	while(K!=1){
		n+=F[K];
		a[++a[0]]=F[K];
		K/=(1ll<<F[K])-1;
	}
	printf("%lld\n",n);
	printf("1 ");
	for(ll i=1;i<=tot;i++)printf("2 ");
	printf("3 ");
	int t=1;
	for(ll i=1;i<=a[0];i++){
		for(ll j=1;j<=a[i];j++)printf("%d ",t);
		t=4-t;
	}
	return 0;
}