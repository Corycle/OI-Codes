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
const int M=1<<7;
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double f[N][M],Ans;
int n,t,C,Sta,a[N];
double Pow(double x,int y){
	double ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot;
		tot=tot*tot;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();C=read();
	for(int i=0;i<n;i++)a[i]=read();
	sort(a,a+n);Sta=(1<<(n-1))-1;
	do{
		memset(f,0,sizeof(f));
		f[a[n-1]*n][0]=1;
		for(int i=0;i<=n*C;i++){
			for(int j=i;j<=n*C;j++){
				for(int S=0;S<=Sta;S++){
					if(i%n&&!((S>>(i%n-1))&1)){
						int k=min(n*C,max(j,i+a[i%n-1]*n));
						f[k][S|(1<<(i%n-1))]+=f[j][S];
					}
				}
			}
		}
		Ans+=f[n*C][Sta];t++;
	}while(next_permutation(a,a+n-1));
	printf("%.15lf",Ans/t/Pow(C,n-1));
	return 0;
}
