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
const int M=1<<10;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,cnt,Sta;
int h[N],vis[N],f[N][M],g[M],Ans[M],sta[M];
struct edge{int to,next,dist;}d[N*20];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
queue<int>q;
void SPFA(int S){
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(f[y][S]>f[x][S]+d[i].dist){
				f[y][S]=f[x][S]+d[i].dist;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
}
void Steiner_Tree(){
	Sta=(1<<K)-1;
	memset(f,0x3f,sizeof(f));
	memset(g,0x3f,sizeof(g));
	for(int i=1;i<=n;i++){
		if(i<=K)f[i][1<<(i-1)]=0;
		else f[i][0]=0;
	}
	for(int S=1;S<=Sta;S++){
		for(int i=1;i<=n;i++){
			for(int T=S;T;T=(T-1)&S){
				f[i][S]=min(f[i][S],f[i][T]+f[i][S^T]);
			}
			if(f[i][S]!=inf){q.push(i);vis[i]=1;}
		}
		SPFA(S);
		for(int i=1;i<=n;i++)g[S]=min(g[S],f[i][S]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	Steiner_Tree();K>>=1;Sta=(1<<K)-1;
	for(int i=1;i<=K;i++)sta[i]=3<<(2*(i-1));
	for(int i=1;i<=Sta;i++)Ans[i]=inf;
	for(int S=1;S<=Sta;S++){
		for(int T=S;T;T=(T-1)&S){
			int t=0;
			for(int i=1;i<=K;i++)if((T>>(i-1))&1)t|=sta[i];
			Ans[S]=min(Ans[S],Ans[S^T]+g[t]);
		}
	}
	printf("%d",(Ans[Sta]!=inf?Ans[Sta]:-1));
	return 0;
}