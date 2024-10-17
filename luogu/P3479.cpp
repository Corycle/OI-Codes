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
const int M=22;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,K,Ans,f[N][M],g[N][M];
void DFS(int x,int fa){
	for(auto y:G[x]){
		if(y==fa)continue;DFS(y,x);
		for(int i=1;i<=K;i++){
			g[x][i]+=g[y][i-1];
			f[x][i]=min(f[x][i]+f[y][i-1],n);
		}
	}
	g[x][0]++;
	if(g[x][K]){
		int num=(int)(ceil(1.0*g[x][K]/m));
		f[x][0]=min(1ll*n,1ll*num*m);Ans+=num;
	}
	for(int i=0;i<=K;i++){
		int dlt=min(g[x][i],f[x][K-i]);
		g[x][i]-=dlt;f[x][K-i]-=dlt;
	}
	for(int i=0;i<=K-1;i++){
		int dlt=min(g[x][i],f[x][K-i-1]);
		g[x][i]-=dlt;f[x][K-i-1]-=dlt;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
	DFS(1,0);
	int num=0;
	for(int i=0;i<=K;i++){
		for(int j=K-i;j>=0;j--){
			int dlt=min(g[1][i],f[1][j]);
			g[1][i]-=dlt;f[1][j]-=dlt;
		}
	}
	for(int i=0;i<=K;i++)num+=g[1][i];
	Ans+=(int)(ceil(1.0*num/m));
	printf("%d\n",Ans);
	return 0;
}
