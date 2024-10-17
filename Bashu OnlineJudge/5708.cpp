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
const double eps=1e-9;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,tot;
double K[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++){
			int sx=read(),sy=read();
			int tx=read(),ty=read();
			if(sx==tx)K[i]=inf;
			else K[i]=(double)(sy-ty)/(sx-tx);
		}
		sort(K+1,K+n+1);
		K[0]=-inf;tot=0;
		for(int i=1;i<=n;i++){
			if(fabs(K[i]-K[i-1])<eps)continue;
			tot++;
		}
		if(n==2&&tot==2)puts("1");
		else if(tot==1)puts("0");
		else if(tot==2)puts("2");
		else puts("3");
	}
	return 0;
}