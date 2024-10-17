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
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f1=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f1=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f1;
}
ll n,cnt;
ll a[N],h[N],f1[N],f2[N],s1[N],s2[N],fa[N],pre[N];
struct edge{ll to,next,cost;}d[N*2];
bool cmp1(ll x,ll y){return f1[x]<f1[y];}
bool cmp2(ll x,ll y){return f2[x]>f2[y];}
void Add(ll x,ll y,ll z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
//in = f1[x] -> out = f2[x] 
void DFS(ll x){
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		pre[y]=d[i].cost;
		fa[y]=x;DFS(y);
	}
	f1[x]=pre[x];s1[0]=s2[0]=0;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		if(f2[y]-f1[y]>0)s1[++s1[0]]=y;
		if(f2[y]-f1[y]<0)s2[++s2[0]]=y;
	}
	sort(s1+1,s1+s1[0]+1,cmp1);
	sort(s2+1,s2+s2[0]+1,cmp2);
	ll sum=a[x];
	for(ll i=1;i<=s1[0];i++){
		if(sum>=f1[s1[i]])sum+=f2[s1[i]]-f1[s1[i]];
		else{f1[x]+=f1[s1[i]]-sum;sum=f2[s1[i]];}
	}
	for(ll i=1;i<=s2[0];i++){
		if(sum>=f1[s2[i]])sum+=f2[s2[i]]-f1[s2[i]];
		else{f1[x]+=f1[s2[i]]-sum;sum=f2[s2[i]];}
	}
	if(sum>=pre[x])sum-=pre[x];
	else {f1[x]+=pre[x]-sum;sum=0;}
	f2[x]=sum;
}
int main(){
//	freopen("horse.in","r",stdin);
//	freopen("horse.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	DFS(1);
	printf("%lld",f1[1]);
	return 0;
}