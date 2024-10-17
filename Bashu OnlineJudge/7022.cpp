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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,top,pos,Sum,Ans;
int h[N],st[N],f[N][N],g[N][N],dis[N],tmp[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
void DFS(int x,int fa,int dist,int S){
	int tmp=pos;st[++top]=x;dis[x]=dist;
	while(pos<top&&dis[st[pos+1]]<=dist-dis[st[pos+1]])pos++;
	int val=max(dis[st[pos]],dist-dis[st[pos]]);
	if(pos!=top)val=min(val,max(dis[st[pos+1]],dist-dis[st[pos+1]]));
	g[S][x]=(val<=m);
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y!=fa)DFS(y,x,dist+d[i].dist,S);}
	pos=tmp;top--;
}
void Solve(int x,int fa,int dist){
	f[x][x]=0;dis[x]=dist;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		Solve(y,x,dist+d[i].dist);
		memset(tmp,0x3f,sizeof(tmp));
		for(int A=1;A<=n;A++){
			for(int B=1;B<=n;B++){
				if(g[A][B]&&dis[A]>=dis[B])tmp[A]=min(tmp[A],f[x][A]+f[y][B]);
				else tmp[A]=min(tmp[A],f[x][A]+f[y][B]+d[i].dist);
				if(g[B][A]&&dis[B]>=dis[A])tmp[B]=min(tmp[B],f[x][A]+f[y][B]);
			}
		}
		memcpy(f[x],tmp,sizeof(f[x]));
	}
}
int main(){
//	freopen("pruning.in","r",stdin);
//	freopen("pruning.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();m=read();cnt=Sum=0;Ans=inf;
		memset(h,0,sizeof(h));memset(g,0,sizeof(f));memset(f,0x3f,sizeof(f));
		for(int i=1;i<n;i++){int x=read()+1,y=read()+1,z=read();Add(x,y,z);Add(y,x,z);Sum+=z;}
		for(int i=1;i<=n;i++)DFS(i,0,0,i);Solve(1,0,0);
		for(int i=1;i<=n;i++)Ans=min(Ans,f[1][i]);
		printf("%d\n",Sum-Ans);
	}
	return 0;
}