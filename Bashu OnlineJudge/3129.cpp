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
int n,m,h[100005],dfn[100005],low[100005],cnt,tot,st[100005],tp,p[100005],scc,num[100005],b[100005];
struct edge{
	int to,next;
}d[200005];
void hqq_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void tarjan(int x){
	int i,j,k;
	dfn[x]=low[x]=++tot;
	st[++tp]=x;p[x]=1;
	for(i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(p[y])low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		scc++;
		do{
			k=st[tp--];
			p[k]=0;
			num[scc]++;
			b[k]=scc;
		}while(k!=x);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=m;i++){
		int x=read(),y=read();
		hqq_add(x,y);
	}
	for(i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(i=1;i<=n;i++){
		if(num[b[i]]!=1)printf("T\n");
		else printf("F\n");
	}
	return 0;
}