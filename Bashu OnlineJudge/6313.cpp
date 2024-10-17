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
const int inf=0x3f3f3f3f;
const double Dlt=0.64;
const double eps=1e-5;
const int Maxn=1025;
const int M=500005;
const int N=105;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,K,Sta,a[M],s[M];
double c[M],X[M],Y[M],Z[M];
double f[N][N][Maxn],P[Maxn];
double Sqr(double x){return x*x;}
int Sgn(double x){
	if(x>eps)return 1;
	if(x<-eps)return -1;
	return 0;
}
void Solve(){
	Sta=(1<<n)-1;
	for(int i=0;i<=Sta;i++){
		P[i]=1;
		for(int j=1;j<=n;j++){
			if((i>>(j-1))&1)P[i]=P[i]*(1+X[j]);
		}
	}
	for(int i=1;i<=K;i++){
		for(int j=0;j<=i;j++){
			for(int sta=0;sta<=Sta;sta++){
				f[i][j][sta]=-inf;
			}
		}
	}
	for(int i=1;i<=K;i++){
		for(int j=0;j<i;j++){
			for(int S=0;S<=Sta;S++){
				int B=Sta-S;
				if(Sgn(f[i-1][j][S]+inf)==0)continue;
				for(int sta=B;;sta=(sta-1)&B){
					int T=S+sta;
					double y=Y[s[i]]*P[sta];
					if(j)y=y*(1-c[i-j]);
					double dlt=1-Sqr(max(0.0,1-y/Z[i]));
					if(Sgn(dlt-Dlt)<0){
						f[i][i][T]=max(f[i][i][T],f[i-1][j][S]+a[i]*dlt);
					}
					else{
						f[i][j][T]=max(f[i][j][T],f[i-1][j][S]+a[i]*dlt);
					}
					if(!sta)break;
				}
			}
		}
	}
}
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++)X[i]=read()*0.01;
	for(int i=1;i<=m;i++)Y[i]=read();
	for(int i=1;i<K;i++)c[i]=read()*0.01;
	for(int i=1;i<=K;i++){
		a[i]=read();s[i]=read();Z[i]=read();
	}
	if(n==0){
		int lst=0;
		double Ans=0;
		for(int i=1;i<=K;i++){
			double y=Y[s[i]];
			if(lst)y*=(1-c[i-lst]);
			double dlt=1-Sqr(max(0.0,1-y/Z[i]));
			if(Sgn(dlt-Dlt)<0)lst=i;
			Ans+=a[i]*dlt;
		}
		printf("%.2lf",Ans);
		return 0;
	}
	Solve();
	double Ans=0;
	for(int i=0;i<=K;i++){
		for(int j=0;j<=Sta;j++){
			Ans=max(Ans,f[K][i][j]);
		}
	}
	printf("%.2lf",Ans);
	return 0;
}