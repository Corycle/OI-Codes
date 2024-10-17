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
const int M=1<<20;
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,dis[105][105];
int a[N],b[N],L[N],d[N],f[M],vis[N];
int lowbit(int x){return x&(-x);}
void BFS(int sx,int id){
	for(int i=1;i<=n;i++)d[i]=inf;
	queue<int>q;q.push(sx);d[sx]=0;
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=1;i<=p;i++){
			if(x+L[i]<=n){int y=x+L[i];if(d[y]==inf){q.push(y);d[y]=d[x]+1;}}
			if(x-L[i]>=1){int y=x-L[i];if(d[y]==inf){q.push(y);d[y]=d[x]+1;}}
		}
	}
	for(int i=1;i<=m;i++)dis[id][i]=d[a[i]];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read()+1;m=read();p=read();
		for(int i=1;i<=n;i++)a[i]=b[i]=vis[i]=0;
		for(int i=1;i<=m;i++){
			int x=read();
			if(vis[x])continue;
			vis[x]=1;b[x]^=1;b[x+1]^=1;
		}
		m=0;
		for(int i=1;i<=p;i++)L[i]=read();
		for(int i=1;i<=n;i++)if(b[i])a[++m]=i;
		for(int i=1;i<=m;i++)BFS(a[i],i);
		int Sta=(1<<m)-1;f[0]=0;
		for(int i=1;i<=Sta;i++)f[i]=inf;
		for(int S=1;S<=Sta;S++){
			int x=(int)(log(lowbit(S))/log(2))+1;
			for(int y=x+1;y<=m;y++){
				int T=S^(1<<(x-1))^(1<<(y-1));
				f[S]=min(f[S],f[T]+dis[x][y]);
			}
		}
		printf("%d\n",f[Sta]==inf?-1:f[Sta]);
	}
	return 0;
}