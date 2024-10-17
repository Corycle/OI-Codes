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
const double INF=1e100;
const int N=1001;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double f[N][N];
struct Point{
	double x,y;
}p[N];
bool cmp(Point A,Point B){
	return A.x<B.x;
}
double Dist(Point A,Point B){
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		p[i].x=read();
		p[i].y=read();
	}
	sort(p+1,p+n+1,cmp);
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			f[i][j]=INF;
		}
	}
	f[2][1]=Dist(p[1],p[2]);
	for(int i=3;i<=n;i++){
		for(int j=1;j<=i-2;j++)f[i][j]=f[i-1][j]+Dist(p[i-1],p[i]);
		for(int j=1;j<=i-2;j++)f[i][i-1]=min(f[i][i-1],f[i-1][j]+Dist(p[i],p[j]));
	}
	double ans=INF;
	for(int i=1;i<n;i++){
		ans=min(ans,f[n][i]+Dist(p[i],p[n]));
	}
	printf("%.2lf",ans);
	return 0;
}