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
#define inf 0x3f3f3f3f
#define mod 10007
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<long long,vector<long long>,greater<long long> >_;
long long read(){
	long long s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
long long n,h[200005],cnt,v[200005],sum[200005],ans,maxx,max1[200005],max2[200005];
struct edge{
	long long to,next;
}d[400005];
void hqq_add(long long x,long long y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	long long i,j,k;
	n=read();
	for(i=1;i<n;i++){
		long long x=read(),y=read();
		hqq_add(x,y);
		hqq_add(y,x);
	}
	for(i=1;i<=n;i++)v[i]=read();
	for(long long x=1;x<=n;x++){
		for(i=h[x];i;i=d[i].next){
			long long y=d[i].to;
			sum[x]+=v[y];
			if(v[y]>max1[x]){
				max2[x]=max1[x];
				max1[x]=v[y];
			}
			else if(v[y]>max2[x]){
				max2[x]=v[y];
			}
		}
		maxx=max(maxx,max1[x]*max2[x]);
	}
	for(long long x=1;x<=n;x++){
		for(i=h[x];i;i=d[i].next){
			long long y=d[i].to;
			ans=(ans+(sum[x]-v[y])%mod*v[y]%mod)%mod;
		}
	}
	printf("%lld %lld",maxx,ans);
	return 0;
}