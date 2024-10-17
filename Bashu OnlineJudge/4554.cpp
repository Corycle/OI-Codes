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
const int N=200005;
const int M=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,root,top,scc,Ans,step,cnt,blk;
int h[N],dep[N],c[N],dfn[N],b[N];
int st[N],v[N],p[N][20],ans[M],s[N];
struct edge{
	int to,next;
}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct ques{
	int x,y,a,b,id;
}q[M];
bool cmp(ques x,ques y){
	if(b[x.x]==b[y.x])return dfn[x.y]<dfn[y.y];
	return b[x.x]<b[y.x];
}
void dfs(int x,int depth){
	int lst=top;
	dep[x]=depth;
	dfn[x]=++step;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dep[y])continue;
		p[y][0]=x;
		dfs(y,depth+1);
		if(top-lst>=blk){
			scc++;
			while(top>lst)b[st[top--]]=scc;
		}
	}
	st[++top]=x;
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	int k=(int)(log(dep[x])/log(2));
	for(;k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	k=(int)(log(dep[x])/log(2));
	for(;k>=0;k--){
		if(p[x][k]!=p[y][k]){
			x=p[x][k];y=p[y][k];
		}
	}
	return p[x][0];
}
void Rev(int x){
	if(!v[x]){
		v[x]=1;s[c[x]]++;
		if(s[c[x]]==1)Ans++;
	}
	else{
		v[x]=0;s[c[x]]--;
		if(s[c[x]]==0)Ans--;
	}
}
void Climb(int x,int y){
	while(x!=y){
		if(dep[x]<dep[y])swap(x,y);
		Rev(x);x=p[x][0];
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	blk=(int)(sqrt(n));
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		if(x==0||y==0)root=x+y;
		else{Add(x,y);Add(y,x);}
	}
	memset(p,-1,sizeof(p));
	dfs(root,1);
	if(top){scc++;while(top)b[st[top--]]=scc;}
	ST();
	for(int i=1;i<=m;i++){
		q[i].id=i;
		q[i].x=read();q[i].y=read();
		q[i].a=read();q[i].b=read();
		if(dfn[q[i].x]>dfn[q[i].y])swap(q[i].x,q[i].y);
	}
	sort(q+1,q+m+1,cmp);
	int t=lca(q[1].x,q[1].y);
	Climb(q[1].x,q[1].y);
	Rev(t);//+ LCA
	ans[q[1].id]=Ans;
	if(s[q[1].a]&&s[q[1].b]&&q[1].a!=q[1].b)ans[q[1].id]--;
	Rev(t);//- LCA
	for(int i=2;i<=m;i++){
		Climb(q[i-1].x,q[i].x);
		Climb(q[i-1].y,q[i].y);
		t=lca(q[i].x,q[i].y);
		Rev(t);//+ LCA
		ans[q[i].id]=Ans;
		if(s[q[i].a]&&s[q[i].b]&&q[i].a!=q[i].b)ans[q[i].id]--;
		Rev(t);//- LCA
	}
	for(int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}