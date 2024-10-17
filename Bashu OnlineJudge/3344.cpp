#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=1605;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
	一个矩形的两条对角线长度、中点相同
	用（长度，中点坐标）双关键字把 n^2 条边排序 
*/
ll n,m;
double Ans;
struct Point{
	ll x,y;
}P[N];
struct Line{
	Point p;
	ll x,y,dist;
}L[N*N];
ll Sqr(ll x){return x*x;}
Point MidPoint(Point A,Point B){
	return (Point){(A.x+B.x),(A.y+B.y)};
}
double Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
ll Dist(Point A,Point B){
	return Sqr(A.x-B.x)+Sqr(A.y-B.y);
}
bool cmp(Line A,Line B){
	if(A.dist==B.dist){
		if(A.p.x==B.p.x)return A.p.y<B.p.y;
		else return A.p.x<B.p.x;
	}
	else return A.dist<B.dist;
}
bool Same(Line A,Line B){
	if(A.dist!=B.dist)return false;
	if(A.p.x!=B.p.x)return false;
	if(A.p.y!=B.p.y)return false;
	return true;
}
void Update(ll l,ll r){
	for(ll i=l;i<=r;i++){
		for(ll j=i+1;j<=r;j++){
			Ans=max(Ans,abs(Cross(P[L[i].x],P[L[i].y],P[L[j].x])));
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		P[i].x=read();
		P[i].y=read();
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			m++;
			L[m].x=i;L[m].y=j;
			L[m].dist=Dist(P[i],P[j]);
			L[m].p=MidPoint(P[i],P[j]);
		}
	}
	ll l=1,r=1;
	sort(L+1,L+m+1,cmp);
	for(ll i=1;i<=m;i++){
		if(Same(L[l],L[r]))r++;
		else{
			Update(l,r-1);
			l=i;r=i+1;
		}
	}
	Update(l,m);
	printf("%.0lf",Ans);
	return 0;
}