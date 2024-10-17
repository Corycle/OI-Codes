/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
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
const double eps=1e-4;
const int N=6005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,R,C,fa[N];
struct Point{int x,y;}P[N];
int Sqr(int x){return x*x;}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
int Dist(Point A,Point B){return Sqr(A.x-B.x)+Sqr(A.y-B.y);}
bool Check(double dis){
	int S=n+1,T=n+2;
	for(int i=1;i<=T;i++)fa[i]=i;
	for(int i=1;i<=n;i++){
		if(min(P[i].y-1,R-P[i].x)-dis<=eps)fa[Find(S)]=Find(i);
		if(min(P[i].x-1,C-P[i].y)-dis<=eps)fa[Find(T)]=Find(i);
		for(int j=i+1;j<=n;j++){
			double dist=Dist(P[i],P[j]);
			if(dist-dis*dis*4<=eps)fa[Find(i)]=Find(j);
		}
		if(Find(S)==Find(T))return false;
	}
	return Find(S)!=Find(T);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();R=read();C=read();
	for(int i=1;i<=n;i++){
		P[i].x=read();
		P[i].y=read();
	}
	double l=0,r=min(R,C);
	while(r-l>eps){
		double mid=(l+r)/2;
		if(Check(mid))l=mid;
		else r=mid;
	}
	printf("%.2lf",l);
	return 0;
}