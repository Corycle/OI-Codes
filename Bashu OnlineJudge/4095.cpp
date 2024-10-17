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
int n,m,cnt;
int mu[N],Mu[N],vis[N],prime[N];
void Prepare(){
	mu[1]=1;
	for(int i=2;i<=m;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=m;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
	for(int i=1;i<=m;i++)Mu[i]=Mu[i-1]+mu[i];
}
ll S(int l,int r,int n){
	ll ans=0;r=min(r,n);
	for(int i=l,j=0;i<=r;i=j+1){
		j=min(r,n/(n/i));
		ans+=1ll*(n/i)*(j-i+1);
	}
	return ans;
}
ll F(int n,int m){
	ll ans=0;
	for(int i=2;i<=n;i++)ans+=S(i+1,2*i-1,m/i);
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=sqrt(n);Prepare();
	ll Ans=0;
	for(int i=1,j=0;i<=m;i=j+1){
		j=min((int)(sqrt(n/(n/(i*i)))),m/(m/i));
		Ans+=1ll*(Mu[j]-Mu[i-1])*F(m/i,n/(i*i));
	}
	printf("%lld",Ans);
	return 0;
}