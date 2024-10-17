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
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tp,cnt,tot,scc;
int h[N],p[N],b[N],st[N],dfn[N],low[N],vis[N],opp[N];
struct Line{
	int s,t;
}l[N],ans[N];
struct edge{
	int to,next;
}d[N*N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
bool Cross(Line x,Line y){
	if(x.t<=y.s||y.t<=x.s)return 0;
	return 1;
}
void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	p[x]=1;st[++tp]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(p[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x]){
		int k=0;
		scc++;
		do{
			k=st[tp--];
			p[k]=0;
			b[k]=scc;
		}while(k!=x);
	}
}
void Print(Line a){
	int x,y;
	x=a.s/60;y=a.s%60;
	printf("%02d:%02d ",x,y);
	x=a.t/60;y=a.t%60;
	printf("%02d:%02d\n",x,y);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int A=read(),B=read(),C=read(),D=read();
		int lst=read();
		l[i].s=A*60+B;
		l[i].t=A*60+B+lst;
		l[i+n].s=C*60+D-lst;
		l[i+n].t=C*60+D;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(Cross(l[i],l[j])){Add(i,j+n);Add(j,i+n);}
			if(Cross(l[i],l[j+n])){Add(i,j);Add(j+n,i+n);}
			if(Cross(l[i+n],l[j])){Add(i+n,j+n);Add(j,i);}
			if(Cross(l[i+n],l[j+n])){Add(i+n,j);Add(j+n,i);}
		}
	}
	for(int i=1;i<=n*2;i++){
		if(!dfn[i])Tarjan(i);
	}
	for(int i=1;i<=n;i++){
		opp[b[i]]=b[i+n];
		opp[b[i+n]]=b[i];
		if(b[i]==b[i+n]){
			printf("NO");
			return 0;
		}
	}
	printf("YES\n");
	for(int i=1;i<=scc;i++){
		if(!vis[i])vis[opp[i]]=1;
	}
	for(int i=1;i<=n*2;i++){
		if(!vis[b[i]]){
			if(i<=n)ans[i]=l[i];
			else ans[i-n]=l[i];
		}
	}
	for(int i=1;i<=n;i++){
		Print(ans[i]);
	}
	return 0;
}