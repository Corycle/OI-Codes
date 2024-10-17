#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const double eps=1e-5;
const ll N=500005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll A[N],B[N],C[N],D[N];
ll n,m,num,top,tot,cnt=1,ans1,ans2;
ll h[N],st[N],dfn[N],low[N],dis[N];
ll vis[N],vst[N],Circle[N],f[N][2],len[N];
struct edge{ll to,next,data;}d[N*2];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void Tarjan(ll x,ll pre){
	dfn[x]=low[x]=++tot;st[++top]=x;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(i==(pre^1))continue;
		if(!dfn[y]){
			Tarjan(y,i);
			low[x]=min(low[x],low[y]);
		}
		else{
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x]){
		if(st[top]==x){
			top--;
			return;
		}
		ll k=0;
		do{
			k=st[top--];
			Circle[++num]=k;
			vis[k]=1;
		}while(k!=x);
	}
}
void DFS(ll x,ll fa){
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(vis[y]||y==fa)continue;
		DFS(y,x);
		ll dlt=f[y][0]+d[i].data;
		if(f[x][0]<dlt){
			f[x][1]=f[x][0];
			f[x][0]=dlt;
		}
		else f[x][1]=max(f[x][1],dlt);
	}
	ans1=max(ans1,f[x][0]+f[x][1]);
}
ll Dist(ll x,ll y){
	for(ll i=h[x];i;i=d[i].next){
		if(y==d[i].to&&!vst[i]){
			vst[i]=vst[i^1]=1;
			return d[i].data;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	Tarjan(1,0);
	Circle[0]=Circle[num];
	Circle[num+1]=Circle[1];
	for(ll i=1;i<=num;i++)DFS(Circle[i],0);
	for(ll i=1;i<=num;i++)len[i]=Dist(Circle[i],Circle[i+1]);
//	cout<<endl;
//	for(ll i=1;i<=num;i++)cout<<Circle[i]<<" ";cout<<endl;
//	for(ll i=1;i<=num;i++)cout<<len[i]<<" ";cout<<endl;
	ll sum=0,maxx=0;
	for(ll i=1;i<=num;i++){
		sum+=len[i-1];
		ll x=Circle[i];
		A[i]=max(A[i-1],f[x][0]+sum);
		B[i]=max(B[i-1],f[x][0]+sum+maxx);
		maxx=max(maxx,f[x][0]-sum);
	}
	ll dlt=len[num];
	sum=0;maxx=0;len[num]=0;
	for(ll i=num;i>=1;i--){
		sum+=len[i];
		ll x=Circle[i];
		C[i]=max(C[i+1],f[x][0]+sum);
		D[i]=max(D[i+1],f[x][0]+sum+maxx);
		maxx=max(maxx,f[x][0]-sum);
	}
//	for(ll i=1;i<=num;i++)cout<<A[i]<<" ";cout<<endl;
//	for(ll i=1;i<=num;i++)cout<<B[i]<<" ";cout<<endl;
//	for(ll i=1;i<=num;i++)cout<<C[i]<<" ";cout<<endl;
//	for(ll i=1;i<=num;i++)cout<<D[i]<<" ";cout<<endl;
	ans2=B[num];
	for(ll i=1;i<num;i++){
		ll tmp=max(max(B[i],D[i+1]),A[i]+C[i+1]+dlt);
		ans2=min(ans2,tmp);
	}
//	cout<<dlt<<endl;
//	cout<<ans1<<" "<<ans2<<endl;
	printf("%.1lf",max(ans1,ans2)/2.0);
	return 0;
}