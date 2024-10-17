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
const double eps=1e-12;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,h[N],fa[N];
double Ans,p[N],f[N],g[N];
struct edge{int to,next;double p;}d[N*2];
void Add(int x,int y,double z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void DFS1(int x){
	f[x]=1-p[x];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS1(y);
		f[x]*=(1-d[i].p*(1-f[y]));
	}
}
void DFS2(int x){
	if(fa[x])f[fa[x]]=g[x];
	f[x]=1-p[x];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		f[x]*=(1-d[i].p*(1-f[y]));
	}
	Ans+=1-f[x];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		g[y]=f[x]/(1-d[i].p*(1-f[y])+eps);
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y!=fa[x])DFS2(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		double z=read()/100.0;
		Add(x,y,z);Add(y,x,z);
	}
	for(int i=1;i<=n;i++)p[i]=read()/100.0;
	DFS1(1);DFS2(1);
	printf("%.6lf",Ans);
	return 0;
}