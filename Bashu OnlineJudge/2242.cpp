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
#define lson x<<1,l,mid
#define rson x<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2050;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
int a[N],c[N],t[N],g[N][N],f[N][N],F[N][N];
void Prepare(int x,int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	Prepare(lson);Prepare(rson);
	for(int i=l;i<=mid;i++){
		for(int j=mid+1;j<=r;j++){
			f[i][x]+=g[i][j];
			f[j][x]+=g[i][j];
		}
	}
}
void DFS(int x,int l,int r){
	if(l==r){
		F[x][a[l]]=0;F[x][a[l]^1]=c[l];
		for(int p=x>>1;p;p>>=1)F[x][t[p]]+=f[l][p];
		return;
	}
	int L=x<<1,R=x<<1|1;
	int mid=(l+r)>>1,len=(r-l+1)/2;
	memset(F[x],0x3f,sizeof(F[x]));
	
	t[x]=1;DFS(lson);DFS(rson);
	for(int i=0;i<=len;i++){
		for(int j=0;j<=len;j++){
			if(i+j<=len)F[x][i+j]=min(F[x][i+j],F[L][i]+F[R][j]);
		}
	}
	t[x]=0;DFS(lson);DFS(rson);
	for(int i=0;i<=len;i++){
		for(int j=0;j<=len;j++){
			if(i+j>len) F[x][i+j]=min(F[x][i+j],F[L][i]+F[R][j]);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=1<<n;
	for(int i=1;i<=m;i++)a[i]=read();
	for(int i=1;i<=m;i++)c[i]=read();
	for(int i=1;i<=m;i++){
		for(int j=i+1;j<=m;j++){
			g[i][j]=g[j][i]=read();
		}
	}
	Ans=inf;
	Prepare(1,1,m);DFS(1,1,m);
	for(int i=0;i<=m;i++)Ans=min(Ans,F[1][i]);
	printf("%d",Ans);
	return 0;
}