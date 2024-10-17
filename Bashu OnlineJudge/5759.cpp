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
const double eps=1e-10;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,R0,cnt,mu[N],vis[N],prime[N];
void Prepare(int maxn){
	mu[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
}
ll Solve(int p){
	ll ans=0;
	double Max=pow(1e6/(1.0*R0*p),2);
	for(int i=1;i<=n/p&&1ll*i*i<=Max;i++){
		ans+=max(min(n/p,(int)(sqrt(Max-1.0*i*i)-eps)),0);
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare(1e6);Ans=2;
	n=read()-1;R0=read();
	int Max=min((int)(1e6/R0),n);
	for(int i=1;i<=Max;i++){
		if(mu[i])Ans+=mu[i]*Solve(i);
	}
	printf("%lld",Ans);
	return 0;
}