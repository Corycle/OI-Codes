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
const int N=10000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int prime[N],mu[N],vis[N],cnt,n;
ll sum[N];
void Prepare(){
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
	for(int j=1;j<=cnt;j++){
		for(int i=1;i*prime[j]<=n;i++){
			sum[i*prime[j]]+=(ll)mu[i];
		}
	}
	for(int i=1;i<=n;i++){
		sum[i]+=sum[i-1];
	}
}
ll Ask(int n,int m){
	if(n>m)swap(n,m);
	ll ans=0,lst=0;
	for(int i=1;i<=n;i=lst+1){
		lst=min(n/(n/i),m/(m/i));
		ans+=(ll)(n/i)*(ll)(m/i)*(sum[lst]-sum[i-1]);
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	Prepare();
	printf("%lld",Ask(n,n));
	return 0;
}