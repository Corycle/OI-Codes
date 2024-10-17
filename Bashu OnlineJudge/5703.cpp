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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
	f[x][0] 不向上延展 
	f[x][1] 可向上延展 
	f[x][2] 某1个儿子中必须延展 
	f[x][3] 某2个儿子中必须延展1个 
*/
int n,cnt;
int h[N],deg[N],f[N][4];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(int x,int fa){
	f[x][0]=f[x][1]=f[x][2]=f[x][3]=inf;
	if(deg[x]==1){f[x][1]=0;return;}
	f[x][0]=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;DFS(y,x);
		int f0=f[x][0],f1=f[x][1],f2=f[x][2],f3=f[x][3];
		f[x][0]=min(inf,min(f0+f[y][0],min(f1,f2)+min(f[y][1],f[y][2])+1));
		f[x][1]=min(inf,min(f0+f[y][1],min(f1+f[y][0],min(f3+f[y][2],f3+f[y][1])+1)));
		f[x][2]=min(inf,min(f2+f[y][0],f0+f[y][2]));
		f[x][3]=min(inf,min(f2+f[y][1],min(f1+f[y][2],min(f3+f[y][0],f1+f[y][1]))));
	}
	f[x][2]=min(f[x][2],f[x][3]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
		deg[x]++;deg[y]++;
	}
	int Root=1;
	for(int i=1;i<=n;i++)if(deg[i]!=1)Root=i;
	DFS(Root,0);
	if(n==2){puts("0");return 0;}
	printf("%d",min(f[Root][0],f[Root][1]));
	return 0;
}