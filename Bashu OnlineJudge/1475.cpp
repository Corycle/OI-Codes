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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,top,scc;
int h[N],dep[N],st[N],b[N],rt[N];
struct edge{
	int to,next;
}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void dfs(int x,int depth){
	dep[x]=depth;
	int lst=top;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dep[y])continue;
		dfs(y,depth+1);
		if(top-lst>=m){
			rt[++scc]=x;
			while(top>lst)b[st[top--]]=scc;
		}
	}
	st[++top]=x;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	dfs(1,1);
	while(top){
		b[st[top--]]=scc;
	}
	printf("%d\n",scc);
	for(int i=1;i<=n;i++)printf("%d ",b[i]);
	printf("\n");
	for(int i=1;i<=scc;i++)printf("%d ",rt[i]);
	return 0;
}