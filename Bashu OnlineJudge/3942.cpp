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
const int inf=0x3f3f3f3f;
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double a[N][N],P[N],F[N*N];
int n,m,cnt,maxn,h[N],num[N];
struct Edge{int s,t;}e[N*N*2];
struct edge{int to,next;}d[N*N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Deal(int x){
	int k=x;
	double p=0,Max=abs(a[x][x]);
	for(int i=x+1;i<=maxn;i++){
		if(abs(a[i][x])>Max){
			Max=abs(a[i][x]);k=i;
		}
	}
	swap(a[x],a[k]);
	for(int i=x+1;i<=maxn;i++){
		p=a[i][x]/a[x][x];
		for(int j=x;j<=maxn+1;j++){
			a[i][j]-=p*a[x][j];
		}
	}
}
void Gauss(){
	for(int i=1;i<=maxn;i++)Deal(i);
	for(int i=maxn;i>=1;i--){
		for(int j=maxn;j>i;j--)a[i][maxn+1]-=a[i][j]*P[j];
		P[i]=a[i][maxn+1]/a[i][i];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		Add(e[i].s,e[i].t);
		Add(e[i].t,e[i].s);
		num[e[i].s]++;num[e[i].t]++;
	}
	a[1][n]=1;
	for(int x=1;x<n;x++){
		a[x][x]=1;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(y!=n)a[x][y]=-1.0/num[y];
		}
	}
	maxn=n-1;Gauss();
	for(int i=1;i<=m;i++){
		int x=e[i].s,y=e[i].t;
		if(x!=n)F[i]+=P[x]/num[x];
		if(y!=n)F[i]+=P[y]/num[y];
	}
	double ans=0;
	sort(F+1,F+m+1);
	for(int i=1;i<=m;i++){
		ans+=(m-i+1)*F[i];
	}
	printf("%.3lf",ans);
	return 0;
}