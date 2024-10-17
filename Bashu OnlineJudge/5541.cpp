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
const ll N=300005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,h[N];
struct Node{ll x,y;}f[N][3];
struct edge{ll to,next,data;}d[N*2];
void Add(ll x,ll y,ll z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
Node Max(Node A,Node B){return (A.x==B.x)?(A.y<B.y?A:B):(A.x>B.x?A:B);}
Node operator+(Node A,Node B){return (Node){A.x+B.x,A.y+B.y};}
Node operator+(Node A,ll B){return (Node){A.x+B,A.y};}
void DFS(ll x,ll fa,ll p){
	f[x][0]=(Node){0,0};
	f[x][1]=(Node){0,0};
	f[x][2]=Max((Node){-p,1},(Node){0,0});
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;if(y==fa)continue;DFS(y,x,p);
		f[x][2]=Max(f[x][2],Max(f[x][2]+f[y][0],f[x][1]+f[y][1]+d[i].data+(Node){-p,1}));
		f[x][1]=Max(f[x][1],Max(f[x][1]+f[y][0],f[x][0]+f[y][1]+d[i].data));
		f[x][0]=Max(f[x][0],f[x][0]+f[y][0]);
	}
	f[x][0]=Max(f[x][0],(Node){0,0});
	f[x][0]=Max(f[x][0],Max(f[x][1]+(Node){-p,1},f[x][2]));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read()+1;
	for(ll i=1;i<n;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	ll l=-1e8,r=1e8,ans=0;
	while(l<=r){
		ll mid=(l+r)>>1;
		DFS(1,0,mid);
		if(f[1][0].y==m){
			printf("%lld",f[1][0].x+m*mid);
			return 0;
		}
		if(f[1][0].y<=m){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	DFS(1,0,ans);
	printf("%lld",f[1][0].x+ans*m);
	return 0;
}