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
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<ll,int>Mu;
int n,cnt,mu[N],vis[N],prime[N];
void Prepare(){
	mu[1]=1;n=1e7;
	for(int i=2;i<=n;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=n;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
	for(int i=2;i<=n;i++)mu[i]+=mu[i-1];
}
int Sum(ll x){
	if(x<=n)return mu[x];
	if(Mu[x])return Mu[x];
	int Ans=1;
	for(ll i=2,j=0;i<=x;i=j+1){
		j=x/(x/i);
		Ans-=(j-i+1)*Sum(x/i);
	}
	return Mu[x]=Ans;
}
int main(){
	ll l=read(),r=read();Prepare();
	printf("%d\n",Sum(r)-Sum(l-1));
	return 0;
}