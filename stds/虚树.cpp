#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,num,cnt,ans;
int h[N],fa[N],dep[N],st[N];
int dfn[N],a[N],dis[N],p[N][25];
struct edge{
	int to,next,data;
}d[N*10];
void Add1(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],z};h[y]=cnt;
}
void Add2(int x,int y){
	ans+=abs(dis[x]-dis[y]);
}
bool cmp(int x,int y){
	return dfn[x]<dfn[y];
}
void DFS(int x,int depth){
	dfn[x]=++num;
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=p[y][0]=x;
		dis[y]=dis[x]+d[i].data;
		DFS(y,depth+1);
	}
}
void ST(){
	int i,j,k=int(log(n)/log(2));
	for(j=1;j<=k;j++){
		for(i=1;i<=n;i++){
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	int k=int(log(dep[x])/log(2));
	for(k;k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	k=int(log(dep[x])/log(2));
	for(k;k>=0;k--){
		if(p[x][k]!=p[y][k]){
			x=p[x][k];
			y=p[y][k];
		}
	}
	return p[x][0];
}
void SvT(){
	ans=0;
	int k=read();
	for(int i=1;i<=k;i++)a[i]=read();
	sort(a+1,a+k+1,cmp);
	int tp=0;
//	for(int i=2;i<=k;i++){
//		if(LCA(a[tot],a[i])!=a[tot]){
//			a[++tot]=a[i];
//		}
//	}
	st[++tp]=1;
	for(int i=1;i<=k;i++){
		int lca=LCA(a[i],st[tp]);
		if(lca==st[tp]){st[++tp]=a[i];continue;}
		while(1){
			if(dep[st[tp-1]]<=dep[lca]){
				Add2(lca,st[tp--]);
				if(st[tp]!=lca)st[++tp]=lca;
				break;
			}
			Add2(st[tp-1],st[tp]);
			tp--;
		}
		if(st[tp]!=a[i])st[++tp]=a[i];
	}
	while(--tp)Add2(st[tp],st[tp+1]);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add1(x,y,z);
	}
	DFS(1,1);
	ST();
	int Case=read();
	while(Case--){
		SvT();
		printf("%d\n",ans);
	}
	return 0;
}
