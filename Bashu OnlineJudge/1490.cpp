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
#define Point Vector
using namespace std;
const int inf=0x3f3f3f3f;
const double Pi=acos(-1);
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double R;
struct Vector{
	double x,y;
	friend Vector operator-(Vector A,Vector B){return (Vector){A.x-B.x,A.y-B.y};}
	friend Vector operator+(Vector A,Vector B){return (Vector){A.x+B.x,A.y+B.y};}
	friend Vector operator*(Vector A,double B){return (Vector){A.x*B,A.y*B};}
	friend Vector operator/(Vector A,double B){return (Vector){A.x/B,A.y/B};}
	friend double operator*(Vector A,Vector B){return A.x*B.x+A.y*B.y;}
	friend double operator^(Vector A,Vector B){return A.x*B.y-A.y*B.x;}
}P[N],O;
double Sqr(double x){return x*x;}
double len(Vector A){return sqrt(Sqr(A.x)+Sqr(A.y));}
double Cross(Point A,Point B,Point C){return (A-C)^(B-C);}
Point Turn(Point A,double a){
	double Sin=sin(a),Cos=cos(a);
	return (Point){A.x*Cos-A.y*Sin,A.x*Sin+A.y*Cos};
}
Point CrossPoint(Point A,Point B,Point C,Point D){
	double s1=Cross(D,B,A),s2=Cross(C,B,A);
	return ((C*s1)-(D*s2))/(s1-s2);
}
Point Circle(Point A,Point B,Point C){
	Vector tAB=Turn(B-A,Pi/2);
	Vector tAC=Turn(C-A,Pi/2);
	Point mAB=(A+B)/2,mAC=(A+C)/2;
	return CrossPoint(mAB,mAB+tAB,mAC,mAC+tAC);
}
void Solve(){
	for(int i=1;i<=n;i++){
		if(len(P[i]-O)<=R)continue;
		O=P[i];
		R=len(P[i]-O);
		for(int j=1;j<i;j++){
			if(len(P[j]-O)<=R)continue;
			O=(P[i]+P[j])/2;
			R=len(P[i]-O);
			for(int k=1;k<j;k++){
				if(len(P[k]-O)<=R)continue;
				O=Circle(P[i],P[j],P[k]);
				R=len(P[i]-O);
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	srand(time(NULL));
	for(int i=1;i<=n;i++)scanf("%lf%lf",&P[i].x,&P[i].y);
	random_shuffle(P+1,P+n+1);
	Solve();
	printf("%.10lf\n",R);
	printf("%.10lf %.10lf",O.x,O.y);
	return 0;
}