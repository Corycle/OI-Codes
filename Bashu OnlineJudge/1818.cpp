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
const int N=100005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;ll a[N];
int h[N],fa[N],dep[N],p[N][M];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(int x,int depth){
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,depth+1);
	}
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int i=1;i<=n;i++)p[i][0]=fa[i];
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	}
	return p[x][0];
}
int Dist(int x,int y){
	return dep[x]+dep[y]-dep[LCA(x,y)]*2;
}
bool cmp(int x,int y){return a[x]<a[y];}
void Query(int x,int y){
	if(Dist(x,y)>=50){printf("Y\n");return;}
	vector<int>V;
	while(x!=y){
		if(dep[x]<dep[y])swap(x,y);
		V.push_back(x);x=fa[x];
	}
	V.push_back(x);
	int num=V.size();
	sort(V.begin(),V.end(),cmp);
	for(int i=0;i<num;i++){
		for(int j=i+1;j<num;j++){
			for(int k=j+1;k<num;k++){
				if(a[V[i]]+a[V[j]]>a[V[k]]){printf("Y\n");return;}
			}
		}
	}
	printf("N\n");
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,1);ST();
	while(m--){
		int op=read(),x=read(),y=read();
		if(op==0)Query(x,y);
		if(op==1)a[x]=y;
	}
	return 0;
}