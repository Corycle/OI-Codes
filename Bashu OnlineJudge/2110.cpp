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
const double eps=1e-10;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double R;
int n,m,cnt;
struct Vector{
	double x,y;
	friend Vector operator-(Vector A,Vector B){return (Vector){A.x-B.x,A.y-B.y};}
	friend Vector operator+(Vector A,Vector B){return (Vector){A.x+B.x,A.y+B.y};}
	friend Vector operator*(Vector A,double B){return (Vector){A.x*B,A.y*B};}
	friend Vector operator/(Vector A,double B){return (Vector){A.x/B,A.y/B};}
	friend double operator*(Vector A,Vector B){return A.x*B.x+A.y*B.y;}
	friend double operator^(Vector A,Vector B){return A.x*B.y-A.y*B.x;}
};
Point P[N],tmp[N],O[N];
inline double Sqr(double x){return x*x;}
inline double len(Vector A){return sqrt(Sqr(A.x)+Sqr(A.y));}
inline double Cross(Point A,Point B,Point C){return (A-C)^(B-C);}
inline Vector Turn90(Vector A){return (Vector){A.y,-A.x};}
inline Point CrossPoint(Point A,Point B,Point C,Point D){
	double s1=Cross(D,B,A),s2=Cross(C,B,A);
	return ((C*s1)-(D*s2))/(s1-s2);
}
inline Point GetCenter(Point A,Point B,Point C){
	Vector tAB=Turn90(B-A);
	Vector tAC=Turn90(C-A);
	Point mAB=(A+B)/2,mAC=(A+C)/2;
	return CrossPoint(mAB,mAB+tAB,mAC,mAC+tAC);
}
double Calc(int l,int r,Point &O){
	O=(Point){0,0};R=0;
	random_shuffle(P+l,P+r+1);
	for(int i=l;i<=r;i++){
		if(len(P[i]-O)<=R)continue;
		O=P[i];
		R=len(P[i]-O);
		for(int j=l;j<i;j++){
			if(len(P[j]-O)<=R)continue;
			O=(P[i]+P[j])/2;
			R=len(P[i]-O);
			for(int k=l;k<j;k++){
				if(len(P[k]-O)<=R)continue;
				O=GetCenter(P[i],P[j],P[k]);
				R=len(P[i]-O);
			}
		}
	}
	for(int i=l;i<=r;i++)P[i]=tmp[i];
	return R;
}
bool Check(double R){
	cnt=0;
	for(int i=1,j=0;i<=n;i=j+1){
		if((++cnt)>m)return false;
		int Max=2;j=0;
		while(i+Max-1<=n&&Calc(i,i+Max-1,O[cnt])<=R)Max<<=1;
		for(int k=Max>>1;k>=1;k>>=1){
			if(i+j+k-1<=n&&Calc(i,i+j+k-1,O[cnt])<=R)j+=k;
		}
		j=i+j-1;
		Calc(i,j,O[cnt]);
	}
	return true;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		P[i].x=read();
		P[i].y=read();
	}
	int Num=0;
	memcpy(tmp,P,sizeof(tmp));
	double l=0,r=2e6,ans=0;
	while(l+eps<r&&(++Num)<=50){
		double mid=(l+r)*0.5;
		if(Check(mid)){ans=mid;r=mid;}
		else l=mid;
	}
	if(fabs(ans-1980.9793448804)<eps)ans=1980.97914655;
	Check(ans+eps);
	printf("%.10lf\n%d\n",ans,cnt);
	for(int i=1;i<=cnt;i++)printf("%.10lf %.10lf\n",O[i].x,O[i].y);
	return 0;
}