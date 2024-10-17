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
const int N=1e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,num,Ans,a[N],b[N],p[N],vis[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++)a[i]=__gcd(n,read());
	for(int i=1;i<m;i++)a[i]=__gcd(a[i],a[m]);
	for(int i=1;1ll*i*i<=a[m];i++)if(a[m]%i==0){b[++cnt]=i;if(i!=a[m]/i)b[++cnt]=a[m]/i;}
	sort(b+1,b+cnt+1);
	ll tmp=a[m];
	for(int i=2;1ll*i*i<=tmp;i++)if(tmp%i==0){p[++num]=i;while(tmp%i==0)tmp/=i;}
	if(tmp!=1)p[++num]=tmp;
	for(int i=1;i<m;i++)vis[lower_bound(b+1,b+cnt+1,a[i])-b]=1;
	for(int i=cnt;i>=1;i--){
		if(vis[i])for(int j=1;j<=num&&p[j]<=b[i];j++)if(b[i]%p[j]==0)vis[lower_bound(b+1,b+cnt+1,b[i]/p[j])-b]=1;
	}
	for(int i=1;i<=cnt;i++)if(!vis[i]){Ans=n/b[i];break;}
	printf("%lld\n",Ans);
	return 0;
}