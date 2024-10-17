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
const int Mod=1e9+7;
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],fa[N],dep[N],sum[N],tmp[N];
int f[N][N],p[N][N],s[N][N*2],c[N][N][N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int mod(int x){return x>=Mod?x-Mod:x;}
void DFS(int x){
	f[x][1]=1;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		DFS(y);
		for(int i=1;i<=sum[x];i++){tmp[i]=f[x][i];f[x][i]=0;}
		for(int i=1;i<=sum[x];i++){
			for(int j=1;j<=sum[y];j++){
				for(int k=1;k<=i+j;k++){
					f[x][k]=mod(f[x][k]+1ll*tmp[i]*f[y][j]%Mod*c[i][j][k]%Mod*p[x][i+j-k]%Mod);
				}
			}
		}
		sum[x]+=sum[y];
	}
}
void Prepare(){
	for(int i=1;i<=n;i++){
		p[i][0]=1;
		for(int j=1;j<=n;j++){
			p[i][j]=1ll*p[i][j-1]*dep[i]%Mod;
		}
	}
	c[0][0][0]=1;
	for(int k=1;k<=n;k++){
		for(int i=0;i<=n;i++){
			for(int j=0;i+j<=n;j++){
				c[i][j][k]=mod(c[i][j][k]+2ll*s[k-1][i-j+n]%Mod);
				c[i][j][k]=mod(c[i][j][k]+mod(s[k-1][i-j-1+n]+s[k-1][i-j+1+n]));
				s[k-1][i-j+n]=mod(s[k-1][i-j+n]+c[i][j][k-1]);
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();dep[1]=1;
	for(int i=2;i<=n;i++){
		Add(fa[i]=read(),i);
		dep[i]=dep[fa[i]]+1;
	}
	Prepare();DFS(1);
	printf("%d",f[1][1]);
	return 0;
}