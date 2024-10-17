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
const double eps=1e-14;
const double D=0.99;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double X,Ans,Best;
int n,m,a[N],b[N],sum[N];
double Sqr(double x){return x*x;}
int Rand(int maxn){return rand()%maxn+1;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	srand(time(NULL));
	n=read();m=read();
	for(int i=1;i<=n;i++){a[i]=read();X+=a[i];}
	X/=m;Best=9e18;
	int Times=1000;
	while(Times--){
		Ans=0;
		for(int i=1;i<=m;i++)sum[i]=0;
		for(int i=1;i<=n;i++){b[i]=Rand(m);sum[b[i]]+=a[i];}
		for(int i=1;i<=m;i++)Ans+=Sqr(sum[i]-X);
		for(double T=1e4;T>eps;T*=D){
			int pos=1,x=Rand(n);
			for(int i=1;i<=m;i++)if(sum[pos]>sum[i])pos=i;
			double tmp=Ans;
			tmp=tmp-Sqr(sum[b[x]]-X)-Sqr(sum[pos]-X);
			sum[b[x]]-=a[x];sum[pos]+=a[x];
			tmp=tmp+Sqr(sum[b[x]]-X)+Sqr(sum[pos]-X);
			if(Best>tmp)Best=tmp;
			if(Ans>tmp||exp((tmp-Ans)/T)<((double)rand()/RAND_MAX)){Ans=tmp;b[x]=pos;}
			else{sum[b[x]]+=a[x];sum[pos]-=a[x];}
		}
	}
	printf("%.2lf",sqrt(Best/m));
	return 0;
}