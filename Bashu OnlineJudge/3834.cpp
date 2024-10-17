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
const int N=1005;
const int M=N*N*2;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,S,T,dlt;
int h[M],dis[M],vis[M];
struct edge{
	int to,next,data;
}d[M*10];
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
	n=read();m=read();
	if(n==1||m==1){
		printf("1");
		return 0;
	}
	dlt=(n-1)*(m-1);
	S=0;T=dlt*2+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			int x=read();
			int p=(i-1)*(m-1)+j;
			if(i==1)Add(S,p+dlt,x);
			if(i==n)Add(p-m+1,T,x);
			if(1<i&&i<n){
				Add(dlt+p,p-m+1,x);
				Add(p-m+1,dlt+p,x);
			}
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			int x=read();
			int p=(i-1)*(m-1)+j;
			if(j==1)Add(p,T,x);
			if(j==m)Add(S,dlt+p-1,x);
			if(1<j&&j<m){
				Add(dlt+p-1,p,x);
				Add(p,dlt+p-1,x);
			}
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			int x=read();
			int p=(i-1)*(m-1)+j;
			Add(p,p+dlt,x);
			Add(p+dlt,p,x);
		}
	}
	SPFA();
	printf("%d",dis[T]);
	return 0;
}