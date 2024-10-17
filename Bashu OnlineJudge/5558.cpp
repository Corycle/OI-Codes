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
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
ll Ans,sum[N],val[N];
int h[N],fa[N],Fa[N],vis[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
struct Node{
	int x;ll sum,val;
	friend bool operator<(Node A,Node B){
		return A.val*B.sum>B.val*A.sum;
	}
};
priority_queue<Node>q;
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(int x){
	vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y]){puts("-1");exit(0);}
		DFS(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","val",stdout);
	n=read();
	for(int i=1;i<=n;i++)Add(Fa[i]=read(),i);
	DFS(0);
	for(int i=0;i<=n;i++){fa[i]=i;sum[i]=1;}
	for(int i=1;i<=n;i++){
		val[i]=read();
		q.push((Node){i,sum[i],val[i]});
		if(!vis[i]){puts("-1");exit(0);}
	}
	while(q.size()){
		Node A=q.top();q.pop();
		int x=Find(A.x),fx=Find(Fa[x]);
		if(sum[x]!=A.sum)continue;
		fa[x]=fx;
		Ans+=1ll*val[x]*sum[fx];
		sum[fx]+=sum[x];
		val[fx]+=val[x];
		if(fx)q.push((Node){fx,sum[fx],val[fx]});
	}
	printf("%lld",Ans);
	return 0;
}