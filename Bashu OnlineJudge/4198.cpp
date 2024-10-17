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
const ll INF=1e18;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Root,Min,top;
ll p[N],q[N],L[N],f[N],dis[N];
int a[N],h[N],fa[N],st[N],sum[N],vis[N];
struct edge{int to,next;ll dist;}d[N];
bool cmp(int x,int y){return dis[x]-L[x]>dis[y]-L[y];}
void Add(int x,int y,ll z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
double Slope(int x,int y){return (double)(f[x]-f[y])/(dis[x]-dis[y]);}
void dfs(int x){a[++a[0]]=x;for(int i=h[x];i;i=d[i].next)if(!vis[d[i].to])dfs(d[i].to);}
void DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		dis[y]=dis[x]+d[i].dist;
		DFS(y);
	}
}
void Find(int x,int num){
	int Max=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		Find(y,num);
		sum[x]+=sum[y];
		Max=max(Max,sum[y]);
	}
	Max=max(Max,num-sum[x]);
	if(Max<=Min){Min=Max;Root=x;}
}
void Divide(int x,int num){
	if(num==1)return;
	Root=0;Min=inf;Find(x,num);
	int rt=Root;
	for(int i=h[rt];i;i=d[i].next){
		vis[d[i].to]=1;
		num-=sum[d[i].to];
	}
	Divide(x,num);a[0]=0;
	for(int i=h[rt];i;i=d[i].next)dfs(d[i].to);
	sort(a+1,a+a[0]+1,cmp);
//	cout<<endl;
//	cout<<"Divide: "<<x<<" "<<num<<":"<<endl;
//	for(int i=1;i<=a[0];i++)cout<<a[i]<<" ";cout<<endl;
	int fx=rt;top=0;
	for(int i=1;i<=a[0];i++){
		int y=a[i];
		while(fx!=fa[x]&&dis[fx]>=dis[y]-L[y]){
			while(top>1&&Slope(st[top-1],st[top])<=Slope(st[top],fx))top--;
			st[++top]=fx;
			fx=fa[fx];
		}
		if(top){
			int l=1,r=top-1,pos=top;
			while(l<=r){
				int mid=(l+r)>>1;
				if(Slope(st[mid],st[mid+1])<p[y]){
					pos=mid;r=mid-1;
				}
				else l=mid+1;
			}
			f[y]=min(f[y],f[st[pos]]+(dis[y]-dis[st[pos]])*p[y]+q[y]);
		}
	}
	for(int i=h[rt];i;i=d[i].next)Divide(d[i].to,sum[d[i].to]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();read();
	for(int i=2;i<=n;i++){
		fa[i]=read();Add(fa[i],i,read());
		p[i]=read();q[i]=read();L[i]=read();
	}
	for(int i=2;i<=n;i++)f[i]=INF;
	DFS(1);Divide(1,n);
	for(int i=2;i<=n;i++)printf("%lld\n",f[i]);
	return 0;
}