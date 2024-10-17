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
const ll N=35;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,K,d[N],C[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=(1ll<<n)-read();
	if(!K){puts("-1");return 0;}
	for(ll i=0;i<=n;i++){
		C[i][0]=1;
		for(ll j=1;j<=i;j++){
			C[i][j]=C[i-1][j-1]+C[i-1][j];
		}
	}
	ll cnt=0;
	while(K>C[n][cnt]){K-=C[n][cnt];cnt++;}
	for(ll i=n,tmp=0;i&&tmp<cnt;i--){
		if(K>C[i-1][cnt-tmp-1])K-=C[i-1][cnt-tmp-1];
		else{tmp++;d[i]=1;}
	}
	for(ll i=1;i<=n;i++)d[i]+=d[i-1];
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			printf("%d ",(j<=d[i]));
		}
		printf("\n");
	}
	return 0;
}