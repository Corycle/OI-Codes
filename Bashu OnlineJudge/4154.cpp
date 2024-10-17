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
const double inf=9e18;
const double eps=1e-15;
const int N=1<<13;
const int M=30;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
double f[N][M];
struct Point{double x,y;}a[M],P[M];
int Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
double Sqr(double x){return x*x;}
double Dist(Point A,Point B){
	return sqrt(Sqr(A.x-B.x)+Sqr(A.y-B.y));
}
bool cmp(Point A,Point B){
	double tmp=Cross(A,B,P[1]);
	if(tmp>eps)return true;
	if(tmp<-eps)return false;
	return Dist(A,P[1])<Dist(B,P[1]);
}
double Solve(int S){
	int id=0;cnt=0;
	double Minx=inf,Miny=inf;
	for(int i=1;i<=n;i++){
		if((S>>(i-1))&1){
			P[++cnt]=a[i];
			if(a[i].y<Miny+eps||((fabs(a[i].y-Miny)<eps)&&a[i].x<Minx+eps)){
				Minx=a[i].x;Miny=a[i].y;id=cnt;
			}
		}
	}
	swap(P[1],P[id]);
	if(cnt<=2)return 0;
	sort(P+2,P+cnt+1,cmp);
	int top=2;
	for(int i=3;i<=cnt;i++){
		while(Cross(P[i],P[top],P[top-1])>-eps)top--;
		P[++top]=P[i];
	}
	double Ans=inf;
	for(int i=1;i<=top;i++)P[i+top]=P[i];
	for(int i=1,j=2;i<=top;i++){
		while(Cross(P[i+1],P[j+1],P[i])>Cross(P[i+1],P[j],P[i]))j++;
		Ans=min(Ans,Cross(P[i+1],P[j],P[i])/Dist(P[i],P[i+1])/2);
	}
	return Ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();m=read();
		for(int i=1;i<=n;i++){
			a[i].x=read();
			a[i].y=read();
		}
		for(int S=1;S<(1<<n);S++){
			for(int i=0;i<=m;i++)f[S][i]=inf;
			f[S][1]=Solve(S);
			for(int T=S;T;T=(T-1)&S){
				for(int i=2;i<=m;i++){
					f[S][i]=min(f[S][i],max(f[T][i-1],f[S^T][1]));
				}
			}
		}
		printf("%.10lf\n",f[(1<<n)-1][m]);
	}
	return 0;
}