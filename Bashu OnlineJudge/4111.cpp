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
ll f[N],g[N],sum[N];
int cnt,vis[N],prime[N];
void Prepare(int maxn){
	f[1]=g[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;f[i]=i-1;g[i]=i;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]){
				f[i*prime[j]]=f[i]*f[prime[j]];
				g[i*prime[j]]=prime[j];
			}
			else{
				g[i*prime[j]]=g[i]*prime[j];
				if(g[i]==i){
					if(i!=prime[j])f[i*prime[j]]=0;
					else f[i*prime[j]]=-prime[j];
				}
				else f[i*prime[j]]=f[i/g[i]]*f[g[i]*prime[j]];
				break;
			}
		}
	}
	for(int i=1;i<=maxn;i++)sum[i]=sum[i-1]+f[i];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();Prepare(1e7);
	while(T--){
		ll Ans=0;
		int n=read(),m=read();
		for(int i=1,j=0;i<=min(n,m);i=j+1){
			j=min(n/(n/i),m/(m/i));
			Ans+=1ll*(n/i)*(m/i)*(sum[j]-sum[i-1]);
		}
		printf("%lld\n",Ans);
	}
	return 0;
}