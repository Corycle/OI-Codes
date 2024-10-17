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
const double INF=1e18;
const double eps=1e-12;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double Ans;
int TestNumber;
int n,m,p0,p1,cnt,h[N];
struct edge{int to,next;}d[N*2];
struct Node{double Power,Point;}P[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
double Sgn(double x){return x>eps?1:(x<-eps?-1:0);}
double Delta(Node A,Node B){
	double dPower=A.Power-B.Power,dPoint=A.Point-B.Point;
	return 2*Sgn(dPower)*(sqrt(abs(dPower)+1)-1)-m*Sgn(dPoint)*(sqrt(abs(dPoint)+1)-1);
}
namespace Task1{
	Node F;
	double f1[N],f2[N];
	void DFS(int x,int fa){
		int num=0;f1[x]=f2[x]=-INF;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(y==fa)continue;
			DFS(y,x);num++;
			if(f1[x]<f1[y]){f2[x]=f1[x];f1[x]=f1[y];}
			else if(f2[x]<f1[y])f2[x]=f1[y];
		}
		double dlt=Delta(F,P[x]);
		f1[x]=max(f1[x],0.0);f1[x]+=dlt;f2[x]+=dlt;
		Ans=max(Ans,f1[x]+f2[x]-dlt+p0);Ans=max(Ans,f1[x]+p0);
	}
	double Calc(double x){Ans=-INF;F=(Node){x,1.0*p0};DFS(1,0);return Ans;}
	void Main(){
		double l=-1e9,r=1e9;
		for(int cnt=1;cnt<=60;cnt++){
			double mid=(l+r)/2;
			if(Sgn(Calc(mid)-p1)>0)r=mid;
			else l=mid;
		}
		printf("%.6lf\n",l);
	}
}
namespace Task2{
	int g1[N],g2[N];
	double f1[N],f2[N],pre[N];
	void DFS1(int x,int fa,double Power){
		f1[x]=p0+Delta((Node){Power,1.0*p0},P[x]);
		g1[x]=x;f2[x]=-INF;g2[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(y==fa)continue;
			DFS1(y,x,Power);
			double tmp=f1[y]+Delta((Node){Power,f1[y]},P[x]);
			if(f1[x]<tmp){f2[x]=f1[x];g2[x]=g1[x];f1[x]=tmp;g1[x]=y;}
			else if(f2[x]<tmp){f2[x]=tmp;g2[x]=y;}
		}
	}
	void DFS2(int x,int fa,double Power){
		if(fa)f1[fa]=pre[x];
		f1[x]=p0+Delta((Node){Power,1.0*p0},P[x]);
		g1[x]=x;f2[x]=-INF;g2[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			double tmp=f1[y]+Delta((Node){Power,f1[y]},P[x]);
			if(f1[x]<tmp){f2[x]=f1[x];g2[x]=g1[x];f1[x]=tmp;g1[x]=y;}
			else if(f2[x]<tmp){f2[x]=tmp;g2[x]=y;}
		}
		Ans=max(Ans,f1[x]);
		for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y!=fa)pre[y]=(g1[x]!=y?f1[x]:f2[x]);}
		for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y!=fa)DFS2(y,x,Power);}
	}
	double Calc(double x){Ans=-INF;DFS1(1,0,x);DFS2(1,0,x);return Ans;}
	void Main(){
		double l=-1e9,r=1e9;
		for(int cnt=1;cnt<=60;cnt++){
			double mid=(l+r)/2;
			if(Sgn(Calc(mid)-p1)>0)r=mid;
			else l=mid;
		}
		printf("%.6lf\n",r);
	}
}
int main(){
//	freopen("pigeatyy.in","r",stdin);
//	freopen("pigeatyy.out","w",stdout);
	TestNumber=read();n=read();p0=read();p1=read();m=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	for(int i=1;i<=n;i++){P[i].Power=read();P[i].Point=read();}
	if(m==0){Task1::Main();return 0;}
	if(m==1){Task2::Main();return 0;}
	return 0;
}