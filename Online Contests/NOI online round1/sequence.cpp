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
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Sum,t[N],sum[N];
ll n,m,cnt,tot,tag;
ll a[N],b[N],fa[N],h[N],vis[N];
struct Node{ll op,x,y;}P[N];
struct edge{ll to,next;}d[N*2];
ll Find(ll x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Add(ll x,ll y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
namespace Task1{
	void Main(){
		if(a[1]-b[1]==a[2]-b[2])puts("YES");
		else puts("NO");
	}
}
namespace Task2{
	void Main(){
		if(a[1]+a[2]==b[1]+b[2])puts("YES");
		else puts("NO");
	}
}
namespace Task3{
	void Main(){
		ll flag=1;
		for(ll i=1;i<=n;i++){
			if(sum[Find(i)])flag=0;
		}
		if(flag==1)puts("YES");
		if(flag==0)puts("NO");
	}
}
void DFS(ll x){
	vis[x]=1;t[++tot]=sum[x];Sum+=sum[x];
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(!vis[y])DFS(y);
		if(x==y)tag=1;
	}
}
bool dfs(ll x,ll s){
//	cout<<s<<endl;
	if(s==Sum/2)return true;
	if(tag&&((Sum-s)%2+2)%2==0)return true;
	if(x==tot+1)return false;
	if(dfs(x+1,s))return true;
	if(dfs(x+1,s+t[x]))return true;
	return false;
}
bool Solve(){
//	cout<<"Solve: "<<endl;
//	for(ll i=1;i<=tot;i++)cout<<t[i]<<" ";cout<<endl;
//	cout<<"Sum: "<<Sum<<" "<<tag<<endl;
	if((Sum%2+2)%2==1)return false;
	return dfs(1,0);
}
int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	ll T=read();
	while(T--){
		n=read();m=read();
		ll Flag1=0,Flag2=0;cnt=0;
		for(ll i=1;i<=n;i++)h[i]=vis[i]=0;
		for(ll i=1;i<=n;i++)a[i]=read();
		for(ll i=1;i<=n;i++)b[i]=read();
		for(ll i=1;i<=m;i++){
			P[i].op=read();
			P[i].x=read();
			P[i].y=read();
			if(P[i].op==1)Flag1=1;
			if(P[i].op==2)Flag2=1;
		}
		if(n==2&&m==1&&P[1].op==1&&P[1].x!=P[1].y){Task1::Main();continue;}
		if(n==2&&m==1&&P[1].op==2&&P[1].x!=P[1].y){Task2::Main();continue;}
		for(ll i=1;i<=n;i++)fa[i]=i;
		for(ll i=1;i<=n;i++)sum[i]=b[i]-a[i];
		for(ll i=1;i<=m;i++){
			if(P[i].op==2){
				ll x=Find(P[i].x),y=Find(P[i].y);
				if(x!=y){fa[x]=y;sum[y]+=sum[x];}
			}
		}
//		cout<<"==========="<<endl;
//		for(ll i=1;i<=n;i++)cout<<Find(i)<<" ";cout<<endl;
//		for(ll i=1;i<=n;i++)cout<<sum[Find(i)]<<" ";cout<<endl;
//		cout<<"==========="<<endl;
		if(Flag2&&!Flag1){Task3::Main();continue;}
		ll flag=1;
		for(ll i=1;i<=m;i++){
			if(P[i].op==1){
				ll x=Find(P[i].x),y=Find(P[i].y);
				Add(x,y);Add(y,x);
			}
		}
		for(ll i=1;i<=n;i++){
			if(i!=Find(i)||vis[i])continue;
			tot=tag=Sum=0;DFS(i);
			if(!Solve())flag=0;
		}
		if(flag==1)puts("YES");
		if(flag==0)puts("NO");
	}
	return 0;
}
