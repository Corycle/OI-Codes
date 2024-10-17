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
const int M=1000005;
const int N=400005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<int,int>vst[M];
int dx[8]={1,0,-1,0,1,-1,1,-1};
int dy[8]={0,1,0,-1,1,1,-1,-1};
int n,R,C,cnt,top,tot,scc,total;
struct edge{int to,next;}d[M],e[M];
struct Point{int x,y,id,type;}P[N];
int h[N],b[N],p[N],H[N],st[N],deg[N],Ans[N],sum[N],dfn[N],low[N],num[N];
bool cmpx(Point A,Point B){return A.x!=B.x?A.x<B.x:A.y<B.y;}
bool cmpy(Point A,Point B){return A.y!=B.y?A.y<B.y:A.x<B.x;}
void Addedge(int x,int y){e[++cnt]=(edge){y,H[x]};H[x]=cnt;}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Tarjan(int x){
	dfn[x]=low[x]=++tot;st[++top]=x;p[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(p[y])low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		int k=0;scc++;
		do{
			k=st[top--];p[k]=0;
			num[scc]+=(k<=n);b[k]=scc;
		}while(x!=k);
	}
}
void Build(){
	for(int i=1;i<=n;i++){
		if(P[i].type!=3)continue;
		for(int j=0;j<8;j++){
			int x=P[i].x+dx[j],y=P[i].y+dy[j];
			if(x<1||y<1||x>R||y>C||!vst[x][y])continue;
			Add(i,vst[x][y]);
		}
	}
	total=n;
	sort(P+1,P+n+1,cmpx);
	for(int i=1,j=0;i<=n;i=j+1){
		j=i;total++;
		while(P[i].x==P[j+1].x)j++;
		for(int k=i;k<=j;k++){
			Add(total,P[k].id);
			if(P[k].type==1)Add(P[k].id,total);
		}
	}
	sort(P+1,P+n+1,cmpy);
	for(int i=1,j=0;i<=n;i=j+1){
		j=i;total++;
		while(P[i].y==P[j+1].y)j++;
		for(int k=i;k<=j;k++){
			Add(total,P[k].id);
			if(P[k].type==2)Add(P[k].id,total);
		}
	}
}
void Solve(){
	queue<int>q;
	for(int i=1;i<=scc;i++){
		if(!deg[i])q.push(i);
		Ans[i]=num[i];
	}
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=H[x];i;i=e[i].next){
			int y=e[i].to;
			Ans[y]=max(Ans[y],Ans[x]+num[y]);
			if(!(--deg[y]))q.push(y);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();R=read();C=read();
	for(int i=1;i<=n;i++){
		P[i].id=i;
		P[i].x=read();
		P[i].y=read();
		P[i].type=read();
		vst[P[i].x][P[i].y]=i;
	}
	Build();
	for(int i=1;i<=total;i++){
		if(!dfn[i])Tarjan(i);
	}
	for(int x=1;x<=total;x++){
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(b[x]!=b[y]){
				deg[b[x]]++;
				Addedge(b[y],b[x]);
			}
		}
	}
	Solve();
	int Max=0;
	for(int i=1;i<=scc;i++)Max=max(Max,Ans[i]);
	printf("%d",Max);
	return 0;
}