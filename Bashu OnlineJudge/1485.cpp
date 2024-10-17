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
const int N=2000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
double p[N],f[N];
double Sqr(double x){return x*x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(scanf("%d",&n)!=EOF){
		int maxn=1<<n;
		memset(f,0,sizeof(f));
		for(int i=1;i<=n;i++)scanf("%lf",&p[i]);
		for(int i=maxn-1;i>=0;i--){
			double P=0,sum=0;
			for(int j=1;j<=n;j++){
				if(!((i>>(j-1))&1)){
					int k=i|(1<<(j-1));
					sum+=f[k]*p[j];
					P+=p[j];
				}
			}
			if(P==0)continue;
			f[i]=(sum+1)/P;
		}
		printf("%.6lf\n",f[0]);
	}
	return 0;
}