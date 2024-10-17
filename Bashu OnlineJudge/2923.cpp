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
const int M=200005;
const int N=40005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,ans;
int h[N],fa[N],vis[N],rd[N];
double Sum,Avg,sum[N],Ans[N];
struct Edge{int s,t;double data;}e[M];
struct edge{int to,next;double data;}d[M];
bool cmp(Edge x,Edge y){
	return x.data<y.data;
}
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
double Sqr(double x){
	return x*x;
}
void Add(int x,int y,double z){
	Sum+=z;rd[x]++;rd[y]++;
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],z};h[y]=cnt;
}
void MST(){
	int num=1;
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=Find(e[i].s);
		int y=Find(e[i].t);
		if(x==y)continue;
		num++;fa[x]=y;
		Add(e[i].s,e[i].t,e[i].data);
		if(num==n)break;
	}
	memset(fa,0,sizeof(fa));
}
void DFS(int x){
	vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y);
		sum[x]+=sum[y]+d[i].data;
	}
	Avg=Sum/rd[x];
	double sum1=Sum-sum[x];
	Ans[x]=Sqr(sum1-Avg);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		Ans[x]+=Sqr(sum[y]+d[i].data-Avg);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		e[i].s=read();e[i].t=read();
		scanf("%lf",&e[i].data);
	}
	MST();
	DFS(1);
	for(int i=1;i<=n;i++){
		if(rd[i]==1)continue;
		if(ans==0||Ans[ans]>Ans[i])ans=i;
	}
	printf("%d",ans);
	return 0;
}