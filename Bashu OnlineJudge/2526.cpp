#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
int n,m,h[2505],cnt,sign,low[2505],dfn[2505],st[2505],tail,scc,bel[2505],ans,d[2505];
struct edge{
	int to,next;
}w[40005];
void add(int x,int y){
	cnt++;
	w[cnt].to=y;
	w[cnt].next=h[x];
	h[x]=cnt;
}
void dfs(int x,int fa){
	dfn[x]=low[x]=++sign;
	st[++tail]=x;
	for(int i=h[x];i;i=w[i].next){
		int to=w[i].to;
		if(to==fa)continue;
		if(!dfn[to])dfs(to,x),low[x]=min(low[x],low[to]);
		else low[x]=min(low[x],dfn[to]);
	}
	if(low[x]==dfn[x]){
		int y;
		scc++;
		do{
			y=st[tail--];
			bel[y]=scc;
		}while(y!=x);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	if(scc==1){
		printf("0");
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int j=h[i];j;j=w[j].next){
			int to=w[j].to;
			if(bel[i]!=bel[to]){
				d[bel[to]]++;
			}
		}
	}
	for(int i=1;i<=scc;i++) if(d[i]==1) ans++;
	if(ans%2==0)printf("%d\n",ans/2);
	else printf("%d\n",(ans-1)/2+1);
	return 0;
}
