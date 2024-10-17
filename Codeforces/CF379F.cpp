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
const int N=1e6+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],p[N][M],dep[N];
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	return p[x][0];
}
int Dist(int x,int y){return dep[x]+dep[y]-dep[LCA(x,y)]*2;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int A=2,B=3,Dis=2;dep[1]=1;
	for(int i=2;i<=4;i++){dep[i]=2;p[i][0]=1;}
	int T=read();n=4;
	while(T--){
		int Fa=read(),x=++n,y=++n,dist=0;
		p[x][0]=p[y][0]=Fa;dep[x]=dep[y]=dep[Fa]+1;
		for(int i=1;i<M;i++)p[x][i]=p[y][i]=p[p[x][i-1]][i-1];
		int pa=A,pb=B;
		dist=Dist(x,pa);if(dist>Dis){Dis=dist;A=x;B=pa;}
		dist=Dist(x,pb);if(dist>Dis){Dis=dist;A=x;B=pb;}
		printf("%d\n",Dis);
	}
	return 0;
}
