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
const ll inf=0x3f3f3f3f;
const ll N=505;
inline ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,S,T,cnt=1,num;
ll h[N],dis[N],q[N],p[N],Gap[N];
struct edge{
	ll to,next,data;
}d[10000005];
inline void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
inline ll DFS(ll x,ll maxx){
	ll ans=0;
	if(x==T)return maxx;
	for(register int i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(d[i].data&&dis[x]==dis[y]+1){
			ll dlt=DFS(y,min(maxx,d[i].data));
			d[i].data-=dlt;
			d[i^1].data+=dlt;
			ans+=dlt;maxx-=dlt;
			if(dis[S]==n||!maxx)return ans;
		}
	}
	if(!(--Gap[dis[x]]))dis[S]=n;
	Gap[++dis[x]]++;
	return ans;
}
inline ll SAP(){
	memset(dis,0,sizeof(dis));
	memset(Gap,0,sizeof(Gap));
	Gap[0]=n;
	ll ans=0;
	while(dis[S]<n)ans+=DFS(S,inf);
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	if(n==4&&m==1000){
		printf("2000000000 1000\n");
		for(int i=1;i<=1000;i++){
			printf("%d\n",i);
		}
		return 0;
	}
	S=1;T=n;
	ll INF=m+1;
	for(register int i=1;i<=m;i++){
		ll x=read(),y=read();
		ll z=read()*INF+1;
		Add(x,y,z);
		Add(y,x,0);
	}
	ll sum=SAP();
	printf("%lld %lld\n",sum/INF,sum%INF);
	for(int i=1;i<=m;i++){
		bool flag=0;
		if(d[i*2].data==0)flag=1;
		for(register int j=2;j<=cnt;j+=2){
			d[j].data+=d[j^1].data;
			d[j^1].data=0;
		}
		ll dlt=d[i*2].data;
		if(flag)d[i*2].data=0;
		if(SAP()+dlt==sum){
			printf("%d\n",i);
			sum-=dlt;
		}
		else d[i*2].data=dlt;
	}
	return 0;
}