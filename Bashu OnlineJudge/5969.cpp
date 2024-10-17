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
const int Mod=10007;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],f[N],sum[N],C[N][N];
struct edge{int to,next;}d[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
int mod(int x){return x>=Mod?x-Mod:x;}
void DFS(int x){
	int flag=0;f[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		DFS(y);
		if(!flag){f[x]=f[y];flag=1;}
		else f[x]=1ll*f[x]*f[y]%Mod*C[sum[x]+sum[y]-1][sum[y]-1]%Mod;
		sum[x]+=sum[y];
	}
	sum[x]++;
}
int main(){
//	freopen("sort.in","r",stdin);
//	freopen("sort.out","w",stdout);
	int Case=read();
	for(int i=0;i<N;i++){C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);}
	while(Case--){
		n=read();cnt=0;
		for(int i=1;i<=n;i++)h[i]=sum[i]=0;
		for(int i=1;i<=n;i++){
			int num=read();
			while(num--)Add(i,read());
		}
		DFS(1);
		printf("%d\n",f[1]);
	}
	return 0;
}