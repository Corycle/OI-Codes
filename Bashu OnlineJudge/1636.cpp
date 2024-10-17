#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int M=505;
const int N=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,Sta,Num,Ans=inf;
int f[M][N][N],belong[M],sta[N];
int a[N][N],b[N][N],c[N][N],vis[N][N];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
struct node{int x,y,S;};
queue<node>q;
void Prepare(){
	for(int S=0;S<=Sta;S++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				f[S][i][j]=inf;
			}
		}
	}
	for(int i=1;i<=Num;i++){
		belong[i]=rand()%K+1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(c[i][j]==-1)continue;
			a[i][j]=belong[c[i][j]];
			f[sta[a[i][j]]][i][j]=b[i][j];
		}
	}
}
void SPFA(){
	while(q.size()){
		int x=q.front().x;
		int y=q.front().y;
		int S=q.front().S;
		q.pop();vis[x][y]=0;
		for(int i=0;i<4;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(fx<1||fx>n||fy<1||fy>m||c[fx][fy]==-1)continue;
			if(f[S|sta[a[fx][fy]]][fx][fy]>f[S][x][y]+b[fx][fy]){
				f[S|sta[a[fx][fy]]][fx][fy]=f[S][x][y]+b[fx][fy];
				if(!vis[fx][fy]&&(S|sta[a[fx][fy]])==S){
					vis[fx][fy]=1;
					q.push((node){fx,fy,S|sta[a[fx][fy]]});
				}
			}
		}
	}
}
void Steiner_Tree(){
	for(int S=0;S<=Sta;S++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(!(S*sta[a[i][j]])||c[i][j]==-1)continue;
				for(int k=S;k;k=(k-1)&S){
					f[S][i][j]=min(f[S][i][j],f[k|sta[a[i][j]]][i][j]+f[(S-k)|sta[a[i][j]]][i][j]-b[i][j]);
				}
				if(f[S][i][j]!=inf){
					q.push((node){i,j,S});
					vis[i][j]=1;
				}
			}
		}
		SPFA();
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			Ans=min(Ans,f[Sta][i][j]);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	srand(time(NULL));
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			c[i][j]=read();
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			b[i][j]=read();
		}
	}
	for(int i=1;i<=K;i++)sta[i]=1<<(i-1);
	Sta=(1<<K)-1;Num=n*m;
	for(int i=1;i<=600;i++){
		Prepare();
		Steiner_Tree();
	}
	if(Ans==inf)Ans=-1;
	printf("%d",Ans);
	return 0;
}