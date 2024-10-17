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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,cnt,Sta;
int a[N],b[N],h[N],sta[N],f[N][M],g[M],vis[M];
struct edge{int to,next,dist;}d[N*10];
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
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=p;i++)f[a[i]][1<<(i-1)]=0;
	for(int i=1;i<=n;i++)f[i][0]=0;
	for(int S=1;S<=Sta;S++){
		for(int i=1;i<=n;i++){
			for(int T=S;T;T=(T-1)&S){
				f[i][S]=min(f[i][S],f[i][T]+f[i][S^T]);
			}
			if(f[i][S]!=inf){q.push(i);vis[i]=1;}
		}
		SPFA(S);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();p=read();Sta=(1<<p)-1;
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	for(int i=1;i<=p;i++){
		b[i]=read();a[i]=read();
		sta[b[i]]|=(1<<(i-1));
	}
	Steiner_Tree();
	memset(g,0x3f,sizeof(g));
	for(int i=1;i<=p;i++)vis[sta[i]]=1;
	for(int S=1;S<=Sta;S++){
		if(!vis[S])continue;
		for(int i=1;i<=p;i++)vis[S|sta[i]]=1;
		for(int i=1;i<=n;i++)g[S]=min(g[S],f[i][S]);
	}
	for(int S=1;S<=Sta;S++){
		for(int T=S;T;T=(T-1)&S){
			g[S]=min(g[S],g[T]+g[S^T]);
		}
	}
	printf("%d",g[Sta]);
	return 0;
}