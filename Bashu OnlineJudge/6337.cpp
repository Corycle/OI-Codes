/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
#define re register int
using namespace std;
const ll inf=9e18;
const ll N=3005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline ll read(){
	ll s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
namespace Data_Maker{
	ll Seed,a,b,c,MOD;
	ll Random(){c++;Seed=(Seed*a+b*c)%MOD;return Seed;}
	ll Random_int(){ll tmp=Random();if(Random()&1)tmp*=-1;return tmp;}
	void Prepare(){Seed=read();a=read();b=read();c=read();MOD=read();}
};
ll n,m,h,Sum,Ans=-inf;
ll a[N][N],sum1[N][N],sum2[N][N],sum[N][N];
void Read(){
	ll type=read();
	if(type==0){
		for(re i=1;i<=n;i++){
			for(re j=1;j<=m;j++){
				a[i][j]=read();
				sum[i][j]=sum[i][j-1]+a[i][j];
			}
		}
	}
	else{
		Data_Maker::Prepare();
		for(re i=1;i<=n;i++){
			for(re j=1;j<=m;j++){
				a[i][j]=Data_Maker::Random_int();
				sum[i][j]=sum[i][j-1]+a[i][j];
			}
		}
	}
}
int main(){
//	freopen("rhombus.in","r",stdin);
//	freopen("rhombus.out","w",stdout);
	n=read();m=read();h=read();Read();
	for(re j=1;j<=m;j++){
		for(re i=1;i<=n;i++)sum1[i][j]=sum1[i-1][j-1]+a[i][j];
		for(re i=n;i>=1;i--)sum2[i][j]=sum2[i+1][j-1]+a[i][j];
	}
	ll s1=h,t1=n-h+1;
	ll s2=h,t2=m-h+1;
	for(re i=s1;i<=t1;i++){
		for(re j=s2;j<=t2;j++){
			if(j==s2){
				Sum=sum[i][j+h-1];
				for(re k=1;k<h;k++){
					Sum+=sum[i-k][j+h-k-1]-sum[i-k][j-h+k];
					Sum+=sum[i+k][j+h-k-1]-sum[i+k][j-h+k];
				}
			}
			else{
				Sum+=a[i][j-h]-a[i][j+h-1];
				Sum+=sum1[i][j+h-1]-sum1[i-h][j-1];
				Sum+=sum2[i][j+h-1]-sum2[i+h][j-1];
				Sum-=sum1[i+h-1][j-1]-sum1[i-1][j-h-1];
				Sum-=sum2[i-h+1][j-1]-sum2[i+1][j-h-1];
			}
			Ans=max(Ans,Sum);
		}
	}
	printf("%lld",Ans);
	return 0;
}