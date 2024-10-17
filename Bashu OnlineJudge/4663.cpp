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
const ll M=10005;
const ll N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
ll A[M][N];
ll idx[M],idy[N];
void Pivot(ll x,ll y){
	swap(idx[x],idy[y]);
	ll tmp=-1/A[x][y];A[x][y]=-1;
	for(ll i=0;i<=m;i++)A[x][i]*=tmp;
	for(ll i=0;i<=n;i++){
		if(i==x||!A[i][y])continue;
		tmp=A[i][y];A[i][y]=0;
		for(ll j=0;j<=m;j++){
			A[i][j]+=tmp*A[x][j];
		}
	}
}
ll Solve(){
	while(1){
		ll x=0,y=0;
		for(ll i=1;i<=m;i++){
			if(A[0][i]>0){
				y=i;break;
			}
		}
		if(!y)return A[0][0];
		ll Min=inf;
		for(ll i=1;i<=n;i++){
			if(A[i][y]>=0)continue;
			ll tmp=-A[i][0]/A[i][y];
			if(tmp<Min){Min=tmp;x=i;}
		}
		if(!x)return inf;
		Pivot(x,y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)A[0][i]=read();
	for(ll i=1;i<=m;i++){
		ll num=read();
		while(num--){
			ll L=read(),R=read();
			for(ll j=L;j<=R;j++)A[i][j]--;
		}
		A[i][0]=read();
	}
	for(ll i=1;i<=m;i++)idx[i]=i+n;
	for(ll i=1;i<=n;i++)idy[i]=i;
	swap(n,m);
	printf("%lld",Solve());
	return 0;
}