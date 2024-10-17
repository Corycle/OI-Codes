#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-5;
const int N=205;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int n,m,cnt;
double ans=inf;
int h[N],a[N][N];
struct edge{
	int to,next,data;
}d[N*N];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
double Ask(int x,int y,int len,double p){
	double Max=0;
	for(int i=1;i<=n;i++){
		Max=max(Max,min(a[i][x]+p,a[i][y]+len-p));
	}
	return Max;
}
void Solve(int x,int y,int len){
	double l=0,r=len;
	while(l+eps<=r){
		double mid1=l+(r-l)/3;
		double mid2=r-(r-l)/3;
		double d1=Ask(x,y,len,mid1);
		double d2=Ask(x,y,len,mid2);
		ans=min(ans,min(d1,d2));
		if(d1>d2)l=mid1;
		else r=mid2;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	memset(a,0x3f,sizeof(a));
	for(int i=1;i<=n;i++)a[i][i]=0;
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		a[x][y]=a[y][x]=z;Add(x,y,z);
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}
	for(int x=1;x<=n;x++){
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			Solve(x,y,d[i].data);
		}
	}
	printf("%.2lf",ans);
	return 0;
}