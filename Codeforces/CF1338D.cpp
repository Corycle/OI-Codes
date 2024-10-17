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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Ans,h[N],f[N][2],deg[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x,int fa){
	f[x][1]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x);
		Ans=max(Ans,f[x][1]+f[y][0]);
		Ans=max(Ans,f[x][0]+max(f[y][0],f[y][1]));
		f[x][0]=max(f[x][0],max(f[y][0],f[y][1])+deg[x]-2);
		f[x][1]=max(f[x][1],f[y][0]+1);
	}
	Ans=max(Ans,max(f[x][0],f[x][1]));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);deg[x]++;deg[y]++;}
	DFS(1,0);
	printf("%d\n",Ans);
	return 0;
}
