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
const int N=2005;
const int M=6005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,k,cnt,ans;
int h[N],sg[N],g[N][N];
struct edge{
	int to,next;
}d[M*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int DFS(int x){
	if(sg[x]>=0)return sg[x];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		g[x][DFS(y)]=1;
	}
	for(int i=0;i<=N;i++){
		if(!g[x][i])return sg[x]=i;
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	memset(sg,-1,sizeof(sg));
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);
	}
	for(int i=1;i<=n;i++){
		if(sg[i]==-1)DFS(i);
	}
	for(int i=1;i<=k;i++){
		ans^=sg[read()];
	}
	if(ans==0)printf("lose");
	else printf("win");
	return 0;
}