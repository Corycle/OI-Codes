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
const ll INF=1e18;
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans,Sum,Min,Answer;
int n,m,cnt,num,h[N],sum[N];
struct Edge{int x,y,val;}E[N];
struct edge{int to,next;ll dist;}d[N*2];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
void DFS1(int x,int fa,ll dist){
	sum[x]=1;Sum+=dist;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS1(y,x,dist+d[i].dist);
		sum[x]+=sum[y];
	}
}
void DFS2(int x,int fa,ll Sum){
	Min=min(Min,Sum);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		Ans+=d[i].dist*sum[y]*(num-sum[y]);
		DFS2(y,x,Sum+d[i].dist*(num-sum[y]*2));
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Answer=INF;
	for(int i=1;i<n;i++){E[i].x=read();E[i].y=read();E[i].val=read();}
	for(int k=1;k<n;k++){
		for(int i=1;i<=n;i++)h[i]=0;cnt=0;
		for(int i=1;i<n;i++)if(i!=k){Add(E[i].x,E[i].y,E[i].val);Add(E[i].y,E[i].x,E[i].val);}
		ll tmp=0;
		Sum=Ans=0;DFS1(E[k].x,0,0);num=sum[E[k].x];Min=INF;DFS2(E[k].x,0,Sum);ll s1=Min,t1=num;tmp+=Ans;
		Sum=Ans=0;DFS1(E[k].y,0,0);num=sum[E[k].y];Min=INF;DFS2(E[k].y,0,Sum);ll s2=Min,t2=num;tmp+=Ans;
		Answer=min(Answer,s1*t2+s2*t1+tmp+t1*t2*E[k].val);
	}
	printf("%lld\n",Answer);
	return 0;
}
