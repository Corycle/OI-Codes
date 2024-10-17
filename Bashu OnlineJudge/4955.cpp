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
#define ull unsigned ll
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-10;
const int Mul=13131;
const int N=305;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
char s[N];
double f[N],p[N],a[N][N];
ull P[N],Hash[N][N];
ull GetHash(int i,int l,int r){
	return Hash[i][r]-Hash[i][l-1]*P[r-l+1];
}
void Gauss(int n){
	for(int i=1;i<=n;i++){
		int t=i;
		for(int j=i;j<=n;j++)if(fabs(a[t][i])<fabs(a[j][i]))t=j;
		if(t!=i)swap(a[i],a[t]);
		for(int j=i+1;j<=n;j++){
			double dlt=a[j][i]/a[i][i];
			for(int k=i;k<=n+1;k++)a[j][k]-=a[i][k]*dlt;
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=i+1;j<=n;j++)a[i][n+1]-=a[i][j]*f[j];
		f[i]=a[i][n+1]/a[i][i];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	P[0]=1;for(int i=1;i<=m;i++)P[i]=P[i-1]*Mul;
	p[0]=1;for(int i=1;i<=m;i++)p[i]=p[i-1]*0.5;
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)Hash[i][j]=Hash[i][j-1]*Mul+s[j];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=m;k++){
				if(GetHash(i,1,k)==GetHash(j,m-k+1,m)){
					a[i][j]+=p[m-k];
				}
			}
		}
		a[i][n+1]=-p[m];
		a[i][n+2]=0;
		a[n+1][i]=1;
	}
	a[n+1][n+2]=1;
	Gauss(n+1);
	for(int i=1;i<=n;i++)printf("%.10lf\n",f[i]);
	return 0;
}