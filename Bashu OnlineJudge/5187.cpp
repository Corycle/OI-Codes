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
const int inf=0x3f3f3f3f;
const int N=50005;
const int M1=225;
const int M2=22;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,cnt;
int a[N],h[N],fa[N],dep[N],p1[N][M1],p2[N][M2],sum[N][M1];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Prepare(int x,int depth){
	p1[x][0]=x;p2[x][0]=fa[x];
	int k=(int)(log(depth)/log(2));
	for(int i=1;i*i<=n;i++)p1[x][i]=fa[p1[x][i-1]];
	for(int i=1;i<=k;i++)p2[x][i]=p2[p2[x][i-1]][i-1];
	for(int i=1;i*i<=n;i++)sum[x][i]=sum[p1[x][i]][i]+a[x];
}
void DFS(int x,int depth){
	dep[x]=depth;
	Prepare(x,depth);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,depth+1);
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p2[x][k];
	}
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p2[x][k]!=p2[y][k]){x=p2[x][k];y=p2[y][k];}
	}
	return fa[x];
}
int Pre(int x,int K){
	int pos=dep[x]-K;
	for(int k=(int)(log(K)/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=pos)x=p2[x][k];
	}
	return x;
}
int Ask1(int x,int y,int k){
	int z=LCA(x,y),Ans=0;
	int dis=dep[x]+dep[y]-dep[z]*2;
	if(x==y)return a[x];if(dis<k)return a[x]+a[y];
	if(dis%k&&x==z)return sum[p1[y][dis%k]][k]-sum[x][k]+a[y]+a[x];
	if(dis%k&&y==z)return sum[x][k]-sum[p1[y][k-dis%k]][k]+a[y];
	if(dis%k){Ans+=a[y];y=p1[y][dis%k];}
	if(dep[y]<dep[z])return Ans+sum[x][k]-sum[p1[z][k-(dep[x]-dep[z])%k]][k];
	if(x==z)return Ans+sum[y][k]-sum[p1[x][k]][k];
	if(y==z)return Ans+sum[x][k]-sum[p1[y][k]][k];
	dis=dep[x]-dep[z];Ans+=sum[x][k]-sum[p1[z][k-dis%k]][k];
	dis=dep[y]-dep[z];Ans+=sum[y][k]-sum[p1[z][k-dis%k]][k];
	if((dep[x]-dep[z])%k==0&&(dep[y]-dep[z])%k==0)Ans-=a[z];
	return Ans;
}
int Ask2(int x,int y,int k){
	int z=LCA(x,y),Ans=0;
	int dis=dep[x]+dep[y]-dep[z]*2;
	if(dis%k){Ans+=a[y];y=Pre(y,dis%k);}
	while(dep[x]>=dep[z]){Ans+=a[x];x=Pre(x,k);}
	while(dep[y]>dep[z]) {Ans+=a[y];y=Pre(y,k);}
	return Ans;
}
int main(){
//	freopen("tourist.in","r",stdin);
//	freopen("tourist.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,1);
	while(m--){
		int x=read(),y=read(),k=read();
		if(k*k<=n)printf("%d\n",Ask1(x,y,k));
		if(k*k>n) printf("%d\n",Ask2(x,y,k));
	}
	return 0;
}