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
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Mod,Ans;
int a[N],h[N],fac[N],inv[N],sum[N],f[N][N],g[N];
struct edge{int to,next,data;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(int maxn){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=maxn;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
void DFS(int x,int fa){
	sum[x]=1;f[x][x!=1]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		a[y]=d[i].data/2;DFS(y,x);
		for(int j=0;j<a[y];j++)f[y][a[y]-j]=1ll*C(a[y]-1,j)*(j&1?Mod-1:1)%Mod;
		for(int j=sum[x];j>=0;j--){
			for(int k=1;k<=a[y];k++){
				f[x][j+k]=mod(f[x][j+k]+1ll*f[x][j]*f[y][k]%Mod*C(j+k,j)%Mod);
			}
			f[x][j]=0;
		}
		sum[x]+=sum[y];
	}
	for(int i=a[x];i<=sum[x];i++)g[x]=mod(g[x]+1ll*f[x][i]*C(i-1,a[x]-1)%Mod);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Mod=read();Prepare(n);
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	a[1]=1;DFS(1,0);Ans=n;
	for(int i=1;i<=n;i++)Ans=1ll*Ans*g[i]%Mod;
	printf("%d",Ans);
	return 0;
}