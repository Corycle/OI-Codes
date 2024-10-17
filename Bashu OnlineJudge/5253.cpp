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
const int N=405;
const int M=N*N;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,S,T;
int a[N][N],h[M],dis[M],vis[M];
struct edge{
	int to,next,data;
}d[M*4];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct cmp{
	bool operator()(int x,int y){
		return dis[x]>dis[y];
	}
};
void SPFA(){
	priority_queue<int,vector<int>,cmp>q;
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	q.push(S);dis[S]=0;
	while(q.size()){
		int x=q.top();q.pop();
		vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>dis[x]+d[i].data){
				dis[y]=dis[x]+d[i].data;
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int p=read();
	while(p--){
		memset(h,0,sizeof(h));
		n=read();cnt=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=read();
			}
		}
		S=0;
		T=(n-1)*(n-1)+1;
		for(int i=1;i<n;i++){
			for(int j=1;j<n;j++){
				int x=(i-1)*(n-1)+j;
				int Rx=x+1,Dx=x+n-1;
				if(j<n-1){
					Add(x,Rx,a[i][j+1]);
					Add(Rx,x,a[i][j+1]);
				}
				if(i<n-1){
					Add(x,Dx,a[i+1][j]);
					Add(Dx,x,a[i+1][j]);
				}
			}
		}
		for(int j=1;j<n;j++){
			Add(S,j,a[1][j]);
			Add((n-1)*(n-2)+j,T,a[n][j]);
		}
		for(int i=1;i<n;i++){
			Add(S,i*(n-1),a[i][n]);
			Add((i-1)*(n-1)+1,T,a[i][1]);
		}
		SPFA();
		printf("%d\n",dis[T]);
	}
	return 0;
}