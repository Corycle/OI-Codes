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
const double eps=1e-8;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,vis[N];
double len[N][N],cost[N][N],d[N][N],dis[N],maxx;
struct Point{int x,y,z;}p[N];
double Sqr(double x){return x*x;}
double Dist(Point x,Point y){
	return sqrt(Sqr(x.x-y.x)+Sqr(x.y-y.y));
}
struct cmp{
	bool operator()(int x,int y){
		return dis[x]>dis[y];
	}
};
double Prime(){
	for(int i=1;i<=n;i++){
		dis[i]=inf;
		vis[i]=0;
	}
	dis[1]=0;
	double ans=0;
	for(int j=1;j<=n;j++){
		int k=0;
		double Min=inf;
		for(int i=1;i<=n;i++){
			if(!vis[i]&&Min>dis[i]){
				Min=dis[i];k=i;
			}
		}
		if(!k)break;
		vis[k]=1;
		ans+=dis[k];
		for(int i=1;i<=n;i++){
			if(!vis[i]&&dis[i]>d[k][i]){
				dis[i]=d[k][i];
			}
		}
	}
	return ans;
}
bool Check(double k){
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			d[i][j]=d[j][i]=cost[i][j]-k*len[i][j];
		}
	}
	return Prime()>=0;
}
double Solve(){
	double l=0,r=maxx,ans=0;
	while(r-l>eps){
		double mid=(l+r)/2.0;
		if(Check(mid)){
			ans=mid;
			l=mid;
		}
		else r=mid;
	}
	return l;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(1){
		n=read();m=0;
		if(!n)break;
		for(int i=1;i<=n;i++){
			p[i].x=read();
			p[i].y=read();
			p[i].z=read();
		}
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				len[i][j]=len[j][i]=Dist(p[i],p[j]);
				cost[i][j]=cost[j][i]=abs(p[i].z-p[j].z);
				maxx=max(maxx,cost[i][j]/len[i][j]);
			}
		}
		printf("%.3lf\n",Solve());
	}
	return 0;
}
/*
题目所求的比率为：r=(∑cost[i]*x[i])/(∑dis[i]*x[i]), 1≤i≤m。
设 x[i]等于 1 或 0，表示边 e[i]是否属于生成树。
为了使 r 最大，设计一个子问题：
令 z(入)=∑(cost[i]*x[i])-入*∑(dis[i]*x[i])=∑x[i]*(cost[i]-入*dis[i])
最大，其中 d[i]=cost[i]-入*dis[i]。
我们可以把 z(入)看做以 d 为边权的最大生成树的总权值。

*/
