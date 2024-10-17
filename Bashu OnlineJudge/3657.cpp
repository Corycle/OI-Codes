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
const ll inf=0x7f7f7f7f7f7f7f7f;
const ll N=10005;
const ll M=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,tot,cnt=1;
ll A,B,num1,num2;
ll a[M][M],h[N],dis[N];
struct edge{ll to,next,flow;}d[N*100];
ll id(ll x,ll y){return (x-1)*m+y;}
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(ll s,ll t){
	memset(dis,-1,sizeof(dis));
	queue<ll>q;q.push(s);dis[s]=0;
	while(q.size()){
		ll x=q.front();q.pop();
		if(x==t)return true;
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;q.push(y);
			}
		}
	}
	return false;
}
ll DFS(ll x,ll maxx,ll t){
	ll ans=0;
	if(x==t||!maxx)return maxx;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			ll dlt=DFS(y,min(d[i].flow,maxx),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
ll Dinic(ll s,ll t){
	ll ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
bool Check(ll val){
	ll sum=0;cnt=1;
	ll S=n*m+1,T=n*m+2;
	memset(h,0,sizeof(h));
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			if(((i+j)&1)==0){
				Add(S,id(i,j),val-a[i][j]);
				sum+=val-a[i][j];
				if(i!=1)Add(id(i,j),id(i-1,j),inf);
				if(j!=1)Add(id(i,j),id(i,j-1),inf);
				if(i!=n)Add(id(i,j),id(i+1,j),inf);
				if(j!=m)Add(id(i,j),id(i,j+1),inf);
			}
			else{
				Add(id(i,j),T,val-a[i][j]);
			}
		}
	}
	return sum==Dinic(S,T);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll Case=read();
	while(Case--){
		n=read();m=read();
		ll Max=0;A=B=num1=num2=0;
		for(ll i=1;i<=n;i++){
			for(ll j=1;j<=m;j++){
				a[i][j]=read();Max=max(Max,a[i][j]);
				if(((i+j)&1)==0){A+=a[i][j];num1++;}
				if(((i+j)&1)==1){B+=a[i][j];num2++;}
			}
		}
		if(num1!=num2){
			ll x=(A-B)/(num1-num2);
			if(x>=Max&&Check(x))printf("%lld\n",x*num1-A);
			else printf("-1\n");
		}
		else{
			if(A!=B)printf("-1\n");
			else{
				ll l=Max,r=inf>>1,ans=-1;
				while(l<=r){
					ll mid=(l+r)>>1;
					if(Check(mid)){
						ans=mid;
						r=mid-1;
					}
					else l=mid+1;
				}
				if(ans==-1)printf("-1\n");
				else printf("%lld\n",ans*num1-A);
			}
		}
	}
	return 0;
}