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
#define pii pair<double,int>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double dis[N],A[N],B[N];
int n,m,cnt,h[N],vis[N];
struct edge{int to,next;double P;}d[N*5];
void Add(int x,int y,double P){
	d[++cnt]=(edge){y,h[x],P};h[x]=cnt;
}
void Dijkstra(){
	priority_queue<pii,vector<pii>,greater<pii> >q;
	for(int i=1;i<=n;i++){dis[i]=inf;A[i]=1;B[i]=0;}
	q.push(mp(0,n));dis[n]=0;
	while(q.size()){
		int x=q.top().scd;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			double P=d[i].P;
			B[y]+=A[y]*P*(dis[x]+1);A[y]*=(1-P);
			//dis[x]是从小到大对dis[y]进行更新的 
			//前面的边全都不能走而这条边可以走那么一定走这条边 
			double E=(A[y]+B[y])/(1-A[y]);
			//C=B/(1-A) , E=\sum_{i=0} (C+i)*(1-A)*A^i
			if(dis[y]>E){dis[y]=E;q.push(mp(dis[y],y));}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(y,x,read()/1000.0);
	}
	Dijkstra();
	printf("%.10lf",dis[1]);
	return 0;
}