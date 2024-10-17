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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,Root,Max,Ans,cnt;
int a[N],b[N],f[N],h[N],son[N];
struct edge{int to,next;}d[N*2];
bool cmp(int x,int y){return x>y;}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Find(int x,int fa,int dist){
	if(dist>Max){Max=dist;Root=x;}
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y!=fa)Find(y,x,dist+1);}
}
void DFS1(int x,int fa){
	f[x]=1;
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y!=fa){DFS1(y,x);if(f[x]<f[y]+1){f[x]=f[y]+1;son[x]=y;}}}
}
void DFS2(int x,int fa,int tp,int dist){
	if(son[x])DFS2(son[x],x,tp,dist+1);
	else b[++tot]=dist;
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y!=fa&&y!=son[x])DFS2(y,x,y,1);}
}
void Solve(int x){
	int ans=0;Root=Max=tot=0;
	for(int i=1;i<=n;i++)f[x]=son[x]=0;
	Find(x,0,1);DFS1(Root,0);DFS2(Root,0,Root,1);
	sort(b+1,b+tot+1,cmp);
	for(int i=1;i<=min(tot,m*2-1);i++)ans+=b[i];
	Ans=max(Ans,ans);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	Solve(1);Solve(Root);
	printf("%d\n",Ans);
	return 0;
}
