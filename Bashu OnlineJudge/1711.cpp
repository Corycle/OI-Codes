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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,num;
int h[205],cnt;
struct Point{
	double x,y;
}p[405],l[405][3][2];
bool cmp(Point A,Point B){
	return (A.x==B.x&&A.y==B.y);
}
double a[205][205];
double Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
int Ask(Point A,Point B,Point C,Point D){
	return (Cross(C,D,A)*Cross(C,D,B)<0)&&(Cross(A,B,C)*Cross(A,B,D)<0);
}
int Check(int x,int y){
	for(int i=1;i<=num;i++){
		for(int j=0;j<3;j++){
			if(cmp(l[i][j][0],l[i][j][1]))continue;
			if(Ask(l[i][j][0],l[i][j][1],p[x],p[y]))return 0;
		}
	}
	return 1;
}
double Dist(Point A,Point B){
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
void Make_edge(){
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			a[i][j]=a[j][i]=inf;
			if(!Check(i,j))continue;
			a[i][j]=a[j][i]=Dist(p[i],p[j]);
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	num=read();
	p[++n]=(Point){0,5};
	p[++n]=(Point){10,5};
	for(int i=1;i<=num;i++){
		double x,sx,sy,fx,fy;
		scanf("%lf%lf%lf%lf%lf",&x,&sx,&sy,&fx,&fy);
		l[i][0][0]=(Point){x,0};
		l[i][0][1]=p[++n]=(Point){x,sx};
		l[i][1][0]=p[++n]=(Point){x,sy};
		l[i][1][1]=p[++n]=(Point){x,fx};
		l[i][2][0]=p[++n]=(Point){x,fy};
		l[i][2][1]=(Point){x,10};
	}
	Make_edge();
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(a[i][k]!=inf&&a[k][j]!=inf)
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}
	printf("%.2lf",a[1][2]);
	return 0;
}