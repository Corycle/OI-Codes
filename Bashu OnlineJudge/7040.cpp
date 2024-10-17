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
const int Inv2=499122177;
const int Mod=998244353;
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int a[N],h[N],f[N][N],tmp[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
int mod(int x){return x>=Mod?x-Mod:x;}
void DFS(int x,int fa){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		for(int j=m;j>=a[y];j--)f[y][j]=1ll*f[x][j-a[y]]*Inv2%Mod;
		DFS(y,x);
		for(int j=0;j<=m;j++)f[x][j]=mod(1ll*f[x][j]*Inv2%Mod+f[y][j]);
	}
}
int main(){
//	freopen("luge.in","r",stdin);
//	freopen("luge.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	f[1][a[1]]=1;DFS(1,0);
	printf("%d\n",f[1][m]);
	return 0;
}