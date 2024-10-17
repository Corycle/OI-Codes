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
const ll inf=9e18;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll f[N],sum[N],Max[N];
int n,m,a[N],b[N],lst[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=m;i++)Max[i]=-inf;
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+b[i];
		f[i]=max(f[i-1],Max[a[i]]+sum[i]);
		Max[a[i]]=max(Max[a[i]],f[i-1]-sum[i-1]);
	}
	printf("%lld",f[n]);
	return 0;
}