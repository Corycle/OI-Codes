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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,top,flag,cnt=1;
int a[N],h[N],st[N],vis[N],ans[N];
struct edge{int to,next;}d[N*4];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x,int pre){
	st[++top]=x;vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(i==(pre^1))continue;
		if(!vis[y])DFS(y,i);
		else if(!flag){
			int k=0,lst=y;flag=1;
			do{k=st[top--];a[k]=1;ans[k]=lst;lst=k;}while(k!=y);
		}
	}
	top--;
}
void dfs(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(ans[y])continue;
		ans[y]=x;dfs(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	for(int x=1;x<=n;x++){
		if(vis[x])continue;
		top=flag=0;DFS(x,0);
		if(!flag){puts("NIE");return 0;}
	}
	puts("TAK");
	for(int i=1;i<=n;i++)if(a[i])dfs(i);
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
	return 0;
}
