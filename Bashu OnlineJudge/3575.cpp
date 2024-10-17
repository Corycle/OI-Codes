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
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m1,m2,tp,cnt,tot,scc;
int dfn[N],low[N],h[N],p[N];
int dis1[N],dis2[N],b[N],st[N];
struct edge{
	int to,next;
}d[N*5];
struct Point{
	int x,y;
}P[N],fr[N],en[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
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
void Prepare(){
	scc=cnt=tot=tp=0;
	memset(d,0,sizeof(d));
	memset(h,0,sizeof(h));
	memset(b,0,sizeof(b));
	memset(p,0,sizeof(p));
	memset(st,0,sizeof(st));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
}
int Dist(Point A,Point B){
	return abs(A.x-B.x)+abs(A.y-B.y);
}
void Build(int maxx){
	Prepare();
	for(int i=1;i<=m1;i++){
		int x=en[i].x,y=en[i].y;
		Add(x,y+n);Add(x+n,y);
		Add(y,x+n);Add(y+n,x);
	}
	for(int i=1;i<=m2;i++){
		int x=fr[i].x,y=fr[i].y;
		Add(x,y);Add(x+n,y+n);
		Add(y,x);Add(y+n,x+n);
	}
	int Len=Dist(P[n+1],P[n+2]);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(dis1[i]+dis1[j]>maxx){Add(i,j+n);Add(j,i+n);}
			if(dis2[i]+dis2[j]>maxx){Add(i+n,j);Add(j+n,i);}
			if(dis1[i]+dis2[j]+Len>maxx){Add(i,j);Add(j+n,i+n);}
			if(dis2[i]+dis1[j]+Len>maxx){Add(j,i);Add(i+n,j+n);}
		}
	}
}
bool Check(){
	for(int i=1;i<=n*2;i++){
		if(!dfn[i])Tarjan(i);
	}
	for(int i=1;i<=n;i++){
		if(b[i]==b[i+n]){
			return false;
		}
	}
	return true;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m1=read(),m2=read();
	P[n+1].x=read();P[n+1].y=read();
	P[n+2].x=read();P[n+2].y=read();
	for(int i=1;i<=n;i++){
		P[i].x=read();P[i].y=read();
		dis1[i]=Dist(P[i],P[n+1]);
		dis2[i]=Dist(P[i],P[n+2]);
	}
	for(int i=1;i<=m1;i++){en[i].x=read();en[i].y=read();}
	for(int i=1;i<=m2;i++){fr[i].x=read();fr[i].y=read();}
	int l=0,r=inf,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		Build(mid);
		if(Check()){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
}