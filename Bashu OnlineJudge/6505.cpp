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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,K,cnt;
int mu[N],num[N],sum[N],vis[N],prime[N];
void Prepare(int maxn){
	mu[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]-=mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
}
ll Calc(int x){
	ll ans=0;
	for(int i=1;1ll*i*i<=x;i++){
		if(x%i==0){
			int a=i,b=x/i;
			ans+=mu[a]*sum[a];
			if(a!=b)ans+=mu[b]*sum[b];
		}
	}
	return ans;
}
void Update(int x,int f){
	num[x]+=f;
	for(int i=1;1ll*i*i<=x;i++){
		if(x%i==0){
			int a=i,b=x/i;
			sum[a]+=f;
			if(a!=b)sum[b]+=f;
		}
	}
}
int main(){
//	freopen("number.in","r",stdin);
//	freopen("number.out","w",stdout);
	n=read();K=read();Prepare(1e5);
	while(n--){
		int op=read(),x=read();
		if(x%K){printf("%lld\n",Ans);continue;}
		x/=K;
		if(op==1){
			Ans+=Calc(x);
			Update(x,1);
		}
		if(op==0){
			if(!num[x]){printf("%lld\n",Ans);continue;}
			Update(x,-1);
			Ans-=Calc(x);
		}
		printf("%lld\n",Ans);
	}
	return 0;
}