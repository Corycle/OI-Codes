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
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int cnt,vis[N],prime[N];
ll mu[N],sum1[N],sum2[N];
void Prepare(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=cnt;j++){
			if(i*prime[j]>n)break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				break;
			}
			else mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<=n;i++)sum1[i]=sum1[i-1]+mu[i];
	for(int i=1;i<=n;i++){
		int lst=0;
		for(int j=1;j<=i;j=lst+1){
			lst=i/(i/j);
			sum2[i]+=1ll*(i/j)*(lst-j+1);
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	Prepare(50000);
	int T=read();
	while(T--){
		int n=read(),m=read();
		if(n>m)swap(n,m);
		ll lst=0,ans=0;
		for(int i=1;i<=n;i=lst+1){
			lst=min(n/(n/i),m/(m/i));
			ans+=sum2[n/i]*sum2[m/i]*(sum1[lst]-sum1[i-1]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}