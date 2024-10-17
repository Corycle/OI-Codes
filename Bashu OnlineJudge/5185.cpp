/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
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
int n,m,Ans;
int a[N],vis[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot;
		tot=tot*tot;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("force.in","r",stdin);
//	freopen("force.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		for(int j=l;j<=r;j++)a[j]=i;
	}
	for(int i=1;i<=n;i++)vis[a[i]]=1;
	for(int i=1;i<=m;i++)Ans+=vis[i];
	printf("%lld",Pow(2ll,Ans));
	return 0;
}
