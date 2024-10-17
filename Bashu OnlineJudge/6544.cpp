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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Lim,Flag;
int f[N],F[N],f1[N],f2[N],num1[N];
int g[N],G[N],g1[N],g2[N],num2[N];
int a[N],b[N],h[N],sum[N],son[N],Sum[N],vis[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS1(int x,int fa){
	vis[x]=1;
	if(a[x]<Lim)return;
	int num=0;f[x]=0;g[x]=sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS1(y,x);
		g[x]&=g[y];
		sum[x]+=sum[y];
		if(g[y])num+=sum[y];
		else f[x]=max(f[x],f[y]);
	}
	if(g[x])f[x]=sum[x];
	else f[x]=f[x]+num+1;
}
void DFS2(int x,int fa){
	if(a[x]<Lim)return;
	if(fa){
		if(a[fa]<Lim)sum[fa]=f[fa]=g[fa]=0;
		else{sum[fa]=Sum[x];f[fa]=F[x];g[fa]=G[x];}
	}
	
	int num=0,tot=0;
	f[x]=0;g[x]=sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		g[x]&=g[y];
		sum[x]+=sum[y];
		if(g[y])num+=sum[y];
		else f[x]=max(f[x],f[y]);
		son[++tot]=d[i].to;
	}
	if(g[x])f[x]=sum[x];
	else f[x]=f[x]+num+1;
	if(f[x]>=m){Flag=1;return;}
	
	f1[0]=f2[tot+1]=0;
	g1[0]=g2[tot+1]=1;
	num1[0]=num2[tot+1]=0;
	for(int i=1;i<=tot;i++){
		int y=son[i];
		f1[i]=f1[i-1];
		g1[i]=g1[i-1]&g[y];
		num1[i]=num1[i-1];
		if(g[y])num1[i]+=sum[y];
		else f1[i]=max(f1[i],f[y]);
	}
	for(int i=tot;i>=1;i--){
		int y=son[i];
		f2[i]=f2[i+1];
		g2[i]=g2[i+1]&g[y];
		num2[i]=num2[i+1];
		if(g[y])num2[i]+=sum[y];
		else f2[i]=max(f2[i],f[y]);
	}
	for(int i=1;i<=tot;i++){
		int y=son[i];
		if(y!=fa){
			Sum[y]=sum[x]-sum[y];
			G[y]=g1[i-1]&g2[i+1];
			if(G[y])F[y]=sum[x]-sum[y];
			else F[y]=max(f1[i-1],f2[i+1])+num1[i-1]+num2[i+1]+1;
		}
	}
	
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS2(y,x);
		if(Flag)return;
	}
}
bool Check(int tmp){
	Flag=0;
	Lim=tmp;
	for(int i=1;i<=n;i++)vis[i]=f[i]=g[i]=sum[i]=0;
	for(int i=1;i<=n;i++){
		if(a[i]>=Lim&&!vis[i]){
			DFS1(i,0);
			DFS2(i,0);
			if(Flag)break;
		}
	}
	return Flag;
}
int main(){
//	freopen("arrange.in","r",stdin);
//	freopen("arrange.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	sort(b+1,b+n+1);
	b[0]=unique(b+1,b+n+1)-b-1;
	int l=1,r=b[0],ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Check(b[mid])){
			ans=b[mid];
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d",ans);
	return 0;
}