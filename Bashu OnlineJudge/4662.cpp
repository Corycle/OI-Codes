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
const double eps=1e-10;
const int N=4005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
int idx[N],idy[N];
int h[N],fa[N],A[N][N];
int dep[N],val[N],pos[N];
struct Edge{int s,t,a,b,w,p;}e[N];
struct edge{int to,next,val,id;}d[N];
void Add(int x,int y,int z,int num){
	d[++cnt]=(edge){y,h[x],z,num};
	h[x]=cnt;
}
void DFS(int x,int depth){
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;
		pos[y]=d[i].id;
		val[y]=d[i].val;
		DFS(y,depth+1);
	}
}
int Check(double x){
	if(x<-eps)return -1;
	if(x>eps)return 1;
	return 0;
}
void Pivot(int x,int y){
	swap(idx[x],idy[y]);
	double tmp=-1/A[x][y];A[x][y]=-1;
	for(int i=0;i<=m;i++)A[x][i]*=tmp;
	for(int i=0;i<=n;i++){
		if(i==x)continue;
		tmp=A[i][y];A[i][y]=0;
		if(Check(tmp)==0)continue;
		for(int j=0;j<=m;j++){
			A[i][j]+=A[x][j]*tmp;
		}
	}
}
double Solve(){
	while(1){
		int x=0,y=0;
		for(int i=1;i<=m;i++){
			if(Check(A[0][i])>0){
				y=i;break;
			}
		}
		if(!y)return A[0][0];
		double Min=inf;
		for(int i=1;i<=n;i++){
			if(Check(A[i][y])>=0)continue;
			double tmp=-A[i][0]/A[i][y];
			if(tmp<Min){Min=tmp;x=i;}
		}
		if(!x)return -1;
		Pivot(x,y);
	}
}
void Prepare(int x,int y,int i){
	while(x!=y){
		if(dep[x]>dep[y]){
			if(val[x]>e[i].w){
				tot++;
				A[i][tot]=-1;
				A[pos[x]][tot]=-1;
				A[0][tot]=val[x]-e[i].w;
			}
			x=fa[x];
		}
		else{
			if(val[y]>e[i].w){
				tot++;
				A[i][tot]=-1;
				A[pos[y]][tot]=-1;
				A[0][tot]=val[y]-e[i].w;
			}
			y=fa[y];
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		e[i].s=read();e[i].t=read();
		e[i].w=read();e[i].p=read();
		e[i].a=read();e[i].b=read();
		if(e[i].p){
			Add(e[i].s,e[i].t,e[i].w,i);
			Add(e[i].t,e[i].s,e[i].w,i);
			A[i][0]=e[i].b;
		}
		else A[i][0]=e[i].a;
	}
	DFS(1,1);
	for(int i=1;i<=m;i++){
		if(e[i].p)continue;
		Prepare(e[i].s,e[i].t,i);
	}
	n=tot;
	for(int i=1;i<=m;i++)idx[i]=i+n;
	for(int i=1;i<=n;i++)idy[i]=i;
	swap(n,m);
	printf("%.0lf",Solve());
	return 0;
}