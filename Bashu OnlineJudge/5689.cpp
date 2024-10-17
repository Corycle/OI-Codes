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
const double eps=1e-7;
const int N=20005;
const int M=10;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double R;
struct Vector{
	double a[M];
	friend Vector operator+(Vector A,Vector B){for(int i=1;i<=m;i++)A.a[i]+=B.a[i];return A;}
	friend Vector operator-(Vector A,Vector B){for(int i=1;i<=m;i++)A.a[i]-=B.a[i];return A;}
	friend double operator*(Vector A,Vector B){double ans=1;for(int i=1;i<=m;i++)ans+=A.a[i]*B.a[i];return ans;}
};
Point A[N],B[N],Ans;
inline double Sqr(double x){return x*x;}
inline double Sqr_Vector(Vector x){return x*x;}
inline double Dist(Vector A,Vector B){return sqrt(Sqr_Vector(B-A));}
inline bool Sgn(double x){return (fabs(x)>eps);}
Vector V[M],D[M],T[M];
Point GetCenter(int n,Point a[]){
	memset(T,0,sizeof(T));
	memset(V,0,sizeof(V));
	memset(D,0,sizeof(D));
	for(int i=1;i<n;i++)V[i]=a[i+1]-a[1];
	for(int i=1;i<n;i++)D[i]=a[i+1]-a[i];
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			T[i].a[n]+=Sqr(V[i-1].a[j])-Sqr(V[i].a[j]);
			for(int k=1;k<=m;k++)T[i].a[j]-=2*V[j].a[k]*D[i].a[k];
		}
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(Sgn(T[j].a[i])){
				swap(T[i],T[j]);
				double dlt=T[j].a[i]/T[i].a[i];
				for(int k=i;k<=n;k++)T[j].a[k]-=dlt*T[i].a[k];
			}
		}
	}
	Point ans=a[1];
	for(int i=n-1;i>=1;i--){
		for(int j=i+1;j<n;j++)T[i].a[n]-=T[j].a[n]*T[i].a[j];
		T[i].a[n]/=T[i].a[i];
		for(int j=1;j<=m;j++)ans.a[j]+=T[i].a[n]*V[i].a[j];
	}
	return ans;
}
void DFS(int x,int y,int maxn){
	if(y>maxn)return;
	if(Dist(A[y],Ans)>R){
		B[x]=A[y];
		Ans=GetCenter(x,B);
		R=Dist(A[y],Ans);
		if(x<=m)DFS(x+1,1,y-1);
	}
	DFS(x,y+1,maxn);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%lf",&A[i].a[j]);
		}
	}
	srand(time(NULL));
	random_shuffle(A+1,A+n+1);
	DFS(1,1,n);
	for(int i=1;i<=m;i++)printf("%.10lf ",Ans.a[i]);
	return 0;
}