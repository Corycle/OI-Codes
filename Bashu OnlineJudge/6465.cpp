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
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,sum,Ans,Max,a[N],p[N];
namespace Task1{
	void DFS(ll x,ll sum1,ll sum2){
		if(x==n+1){
			if(Max<sum1+sum2){Max=sum1+sum2;Ans=min(sum1,sum2);}
			else if(Max==sum1+sum2)Ans=min(Ans,min(sum1,sum2));
			return;
		}
		DFS(x+1,sum1^a[x],sum2);
		DFS(x+1,sum1,sum2^a[x]);
	}
	void Main(){
		for(ll i=1;i<=n;i++)a[i]=read();
		DFS(1,0,0);
		printf("%lld",Ans);
	}
}
namespace Task2{
	void Insert(ll x){
		for(ll i=60;i>=0;i--)if(!((sum>>i)&1)&&((x>>i)&1)){if(p[i])x^=p[i];else{p[i]=x;return;}}
		for(ll i=60;i>=0;i--)if( ((sum>>i)&1)&&((x>>i)&1)){if(p[i])x^=p[i];else{p[i]=x;return;}}
	}
	ll Query(){
		ll ans=0;
		for(ll i=60;i>=0;i--)if(!((sum>>i)&1)&&!((ans>>i)&1))ans^=p[i];
		for(ll i=60;i>=0;i--)if( ((sum>>i)&1)&& ((ans>>i)&1))ans^=p[i];
		return ans;
	}
	void Main(){
		for(ll i=1;i<=n;i++)a[i]=read();
		for(ll i=1;i<=n;i++)sum^=a[i];
		for(ll i=1;i<=n;i++)Insert(a[i]);
		printf("%lld",Query());
	}
}
int main(){
//	freopen("set.in","r",stdin);
//	freopen("set.out","w",stdout);
	n=read();
	if(n<=10)Task1::Main();
	else Task2::Main();
	return 0;
}