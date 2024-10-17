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
const int Mod=998244353;
const int N=5005;
const int M=2505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,cnt;
int a[N],h[N],sum[N],num[N][2],f[N][M],g[N][M],F[N][M];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int mod(int x){return x>=Mod?x=Mod:x;}
void DFS(int x,int fa){
	sum[x]=1;num[x][a[x]]=1;f[x][0]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x);
		for(int j=(sum[x]+sum[y])/2;j>=0;j--)F[x][i]=0;
		for(int j=sum[x]/2;j>=0;j--){
			for(int k=0;k<=sum[y]/2;k++){
				F[x][j+k]=mod(F[x][j+k]+1ll*f[x][j]*f[y][k]%Mod);
				g[x][j+k+1]=mod(g[x][j+k+1]+1ll*f[x][j]*f[y][k]%Mod*(num[y][a[x]^1]-k)%Mod);
			}
		}
		for(int j=(sum[x]+sum[y])/2;j>=0;j--)f[x][i]=F[x][i];
		sum[x]+=sum[y];
		num[x][0]+=num[y][0];
		num[x][1]+=num[y][1];
	}
	for(int i=0;i<=sum[x]/2;i++)f[x][i]=mod(f[x][i]+g[x][i]);
}
int main(){
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	n=read();m=n/2;
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)a[i]=s[i]-'0';
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,0);
	for(int i=0;i<=m;i++)printf("%d ",f[1][i]);
	return 0;
}
