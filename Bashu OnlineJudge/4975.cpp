/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<bitset>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=1e9+7;
const int N=2005;
const int M=305;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt;
int vis[N],prime[N],a[M][M];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(int maxn){
	for(int i=2;i<=maxn;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int Gauss(int n,int m){
	int ans=0;
	for(int i=1;i<=m;i++){
		int t=0;
		for(int j=ans+1;j<=n;j++)if(a[j][i])t=j;
		if(!t)continue;ans++;swap(a[ans],a[t]);
		for(int j=1;j<=n;j++){
			if(j!=ans&&a[j][i]){
				for(int k=i;k<=m;k++)a[j][k]^=a[ans][k];
			}
		}
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	Prepare(2000);
	while(T--){
		n=read();
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++){
			ll x=read();
			for(int j=1;j<=cnt&&prime[j]<=x;j++){
				while(x%prime[j]==0){x/=prime[j];a[j][i]^=1;}
			}
		}
		printf("%d\n",(Pow(2,n-Gauss(cnt,n))-1+Mod)%Mod);
	}
	return 0;
}