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
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
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
int n,m,h[100005],cnt,tot,p[100005],st[100005],dfn[100005],low[100005],tp;
int scc,b[100005],maxx[100005],rd[100005],cntt,h1[100005];
struct edge{
	int fr,to,next;
}d[100005],w[100005];
void hqq_add(int x,int y){
	d[++cnt]=(edge){x,y,h[x]};
	h[x]=cnt;
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
		else if(p[y])low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]){
		scc++;
		do{
			k=st[tp--];
			p[k]=0;
			b[k]=scc;
			maxx[scc]=max(maxx[scc],k);
		}while(k!=x);
	}
}
void add(int x,int y){
	w[++cntt]=(edge){x,y,h1[x]};
	h1[x]=cntt;
}
void topsort(){
	int i,j,k;
	queue<int>q;
	while(q.size())q.pop();
	for(i=1;i<=scc;i++){
		if(rd[i]==0){
			q.push(i);
		}
	}
	while(q.size()){
		int x=q.front();
		q.pop();
		for(i=h1[x];i;i=w[i].next){
			int y=w[i].to;
			maxx[y]=max(maxx[x],maxx[y]);
			rd[y]--;
			if(rd[y]==0){
				q.push(y);
			}
		}
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
	for(i=1;i<=cnt;i++){
		if(b[d[i].fr]!=b[d[i].to]){
			rd[b[d[i].fr]]++;
			add(b[d[i].to],b[d[i].fr]);
		}
	}
	topsort();
	for(i=1;i<=n;i++){
		printf("%d ",maxx[b[i]]);
	}
	return 0;
}