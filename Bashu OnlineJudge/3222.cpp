#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<iomanip>
#define ll long long
#define re register
using namespace std;
int read(){
	int s=0,t=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')t=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*t;
}
const int inf=0x7fffffff;
const double dof=1e+8;
const double eps=1e-8;
const long long lof=9e18;
const int N=305;
struct Edge{int x,y;}E[N*5];
struct edge{int to,next;double v;}e[N*20];
double U,Ans;
int n,m,s,t,Max,cnt,sign;
int h[N],d[N],Gap[N],rd[N],vis[N];
void add(int x,int y,double v){
	e[++cnt]=(edge){y,h[x],v};h[x]=cnt;
	e[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
double dfs(int x,double maxn){
	double ret=0,dlt;
	if(x==t||maxn<eps)return maxn;
	for(int i=h[x];i;i=e[i].next){
		int y=e[i].to;
		if(d[x]==d[y]+1&&e[i].v>eps){
			dlt=dfs(y,min(e[i].v,maxn));
			ret+=dlt,maxn-=dlt;
			e[i].v-=dlt;
			e[i^1].v+=dlt;
			if(d[s]==Max||maxn<eps)return ret;
		}
	}
	if(!(--Gap[d[x]]))d[s]=Max;
	Gap[++d[x]]++;
	return ret;
}
double SAP(){
	double ans=0;
	memset(Gap,0,sizeof(Gap));
	memset(d,0,sizeof(d));
	Gap[0]=Max;
	while(d[s]<Max)ans+=dfs(s,dof);
	return ans;
}
double check(double g){
	cnt=1,s=n+1,t=n+2,Max=n+2;
	memset(e,0,sizeof(e));
	memset(h,0,sizeof(h));
	for(int i=1;i<=m;i++){
		add(E[i].x,E[i].y,1);
		add(E[i].y,E[i].x,1);
	}
	for(int i=1;i<=n;i++){
		add(s,i,U);
		add(i,t,U+2*g-rd[i]);
	}
	return (U*n-SAP())/2;
}
void Dfs(int x){
	vis[x]=1,sign++;
	for(int i=h[x];i;i=e[i].next){
		int y=e[i].to;
		if(!vis[y]&&e[i].v)Dfs(y);
	}
}
void Find(){
	double l=0,r=m,EPS=1.0/n/n;
	while(r-l>EPS){
		double mid=(l+r)/2;
		if(check(mid)>=eps)l=mid,Ans=mid;
		else r=mid;
	}
	check(Ans);
	Dfs(s);
	printf("%d",sign-1);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read(),U=m;
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		E[i]=(Edge){x,y};
		rd[x]++,rd[y]++;
	}
	if(!m)printf("1");
	else Find();
	return 0;
}