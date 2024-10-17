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
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,dfn[105],low[105],h[105],cnt,tot,p[105],f[105],ans;
struct edge{
	int to,next;
}d[20005];
void hqq_add(int x,int y){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	h[x]=cnt;
}
void init(){
	cnt=tot=ans=0;
	memset(d,0,sizeof(d));
	memset(p,0,sizeof(p));
	memset(h,0,sizeof(h));
	memset(f,0,sizeof(f));
	memset(low,0,sizeof(low));
	memset(dfn,0,sizeof(dfn));
}
void tarjan(int x,int fa){
	int i,j,k;
	dfn[x]=low[x]=++tot;
	int son=0;
	for(i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		if(dfn[y]==0){
			tarjan(y,x);
			son++;
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]&&fa!=-1||x==1&&son>1)f[x]=1;
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	while(1){
		init();
		n=read();
		if(n==0)break;
		while(1){
			i=read();
			if(i==0)break;
			while(1){
				scanf("%d",&j);
				hqq_add(i,j);
				hqq_add(j,i);
				char c=getchar();
				if(c==10||c==13)break;
			}
		}
		for(i=1;i<=n;i++){
			if(dfn[i]==0)tarjan(i,-1);
		}
		for(i=1;i<=n;i++)if(f[i])ans++;
		printf("%d\n",ans);
	}
	return 0;
}