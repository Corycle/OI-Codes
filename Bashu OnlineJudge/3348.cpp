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
const int inf=0x3f3f3f3f;
const int N=1e7+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll sum[N];
int cnt,phi[N],vis[N],prime[N];
void Prepare(int maxn){
	phi[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){vis[i]=1;prime[++cnt]=i;phi[i]=i-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]){phi[i*prime[j]]=phi[i]*(prime[j]-1);}
			else{phi[i*prime[j]]=phi[i]*prime[j];break;}
		}
	}
	for(int i=1;i<=maxn;i++)sum[i]=sum[i-1]+phi[i];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare(1e7);
	int T=read();
	while(T--){
		ll Ans=0;
		int n=read();
		for(int i=1,j=0;i<=n;i=j+1){
			j=n/(n/i);
			Ans+=(sum[j]-sum[i-1])*(2*sum[n/i]-1);
		}
		printf("%lld\n",Ans);
	}
	return 0;
}