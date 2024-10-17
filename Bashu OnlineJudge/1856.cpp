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
const int P=3000005;
const int N=1000005;
const int M=27;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll Ans,sum[N];
struct edge{int to,next;}d[N*2];
int n,m,cnt,top,tot=1,lst=1,root=1;
int a[P],fa[N],dfn[N],dep[N],ch[N][M];
int h[N],q[N],st[N],len[N],pos[N],p[N][M];
bool cmp(int x,int y){return dfn[x]<dfn[y];}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Insert(int num){
	int x=lst,fx=++tot;len[fx]=len[x]+1;
	while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
	if(!x)fa[fx]=root;
	else{
		int y=ch[x][num];
		if(len[y]==len[x]+1)fa[fx]=y;
		else{
			int fy=++tot;len[fy]=len[x]+1;
			memcpy(ch[fy],ch[y],sizeof(ch[fy]));
			fa[fy]=fa[y];fa[y]=fa[fx]=fy;
			while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
		}
	}
	lst=fx;
}
void DFS(int x,int depth){
	dep[x]=depth;dfn[x]=++dfn[0];
	for(int i=h[x];i;i=d[i].next){
		DFS(d[i].to,depth+1);
	}
}
void ST(){
	int k=(int)(log(tot)/log(2));
	for(int i=1;i<=tot;i++)p[i][0]=fa[i];
	for(int j=1;j<=k;j++){
		for(int i=1;i<=tot;i++){
			if(p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	}
	return p[x][0];
}
void Solve(int x){
	q[++q[0]]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		Solve(y);
		Ans+=len[x]*sum[x]*sum[y];
		sum[x]+=sum[y];
	}
}
void Build(){
	sort(a+1,a+m+1,cmp);
	st[top=1]=a[1];cnt=0;
	for(int i=2;i<=m;i++){
		int lca=LCA(st[top],a[i]);
		while(top>=2&&dep[lca]<=dep[st[top-1]]){Add(st[top-1],st[top]);top--;}
		if(st[top]!=lca){Add(lca,st[top]);st[top]=lca;}
		st[++top]=a[i];
	}
	while(top>=2){Add(st[top-1],st[top]);top--;}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();int T=read();scanf("%s",s+1);
	for(int i=n;i>=1;i--){
		Insert(s[i]-'a'+1);
		pos[i]=lst;
	}
	for(int i=1;i<=tot;i++)Add(fa[i],i);
	DFS(1,1);ST();
	for(int i=1;i<=tot;i++)h[i]=0;
	while(T--){
		m=read();
		for(int i=1;i<=m;i++)a[i]=pos[read()];
		sort(a+1,a+m+1);
		m=unique(a+1,a+m+1)-a-1;
		for(int i=1;i<=m;i++)sum[a[i]]=1;
		Ans=0;Build();Solve(st[1]);
		while(q[0]){int x=q[q[0]--];sum[x]=h[x]=0;}
		printf("%lld\n",Ans);
	}
	return 0;
}