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
int n,m,cnt,scc,tot,tp;
int w[105],v[105],h[105],dfn[105],low[105],st[105],p[105],b[105];
int head[105],f[105][505],vmain[105],wmain[105],rd[105];
struct edge{
	int fr,to,next;
}d[105],e[105];
void hqq_add(int x,int y){
	d[++cnt]={x,y,h[x]};
	h[x]=cnt;
}
void hqq_add2(int x,int y){
	e[++cnt]={x,y,head[x]};
	head[x]=cnt;
}
void tarjan(int x){
	int i,j,k;
	dfn[x]=low[x]=++tot;
	st[++tp]=x;
	p[x]=1;
	for(i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(p[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x]){
		scc++;
		do{
			k=st[tp--];
			p[k]=0;
			b[k]=scc;
			vmain[scc]+=v[k];
			wmain[scc]+=w[k];
		}while(k!=x);
	}
}
void dfs_dp(int x){
	int i,j,k;
	for(i=m;i>=wmain[x];i--){
		f[x][i]=vmain[x];
	}
	for(i=head[x];i;i=e[i].next){
		int y=e[i].to;
		dfs_dp(y);
		for(j=m;j>=wmain[x];j--){
			for(k=m-j;k>=wmain[y];k--){
				f[x][j+k]=max(f[x][j+k],f[x][j]+f[y][k]);
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++)w[i]=read();
	for(i=1;i<=n;i++)v[i]=read();
	for(i=1;i<=n;i++)hqq_add(read(),i);
	for(i=0;i<=n;i++){
		if(!dfn[i])tarjan(i);
	}
	cnt=0;
	for(i=1;i<=n;i++){
		if(b[d[i].fr]!=b[d[i].to]){
			hqq_add2(b[d[i].fr],b[d[i].to]);
			rd[b[d[i].to]]++;
		}
	}
	for(i=1;i<=scc;i++){
		if(i!=b[0]&&!rd[i]){
			hqq_add2(b[0],i);
		}
	}
	dfs_dp(b[0]);
	printf("%d",f[b[0]][m]);
	return 0;
}