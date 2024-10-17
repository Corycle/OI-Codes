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
const double eps=1e-11;
const int Mod=10007;
const int N=305;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
double d[N][N];
int n,R,a[N][N];
struct Point{int x,y;}P[N];
ll Sqr(ll x){return x*x;}
double Dist(Point A,Point B){return sqrt(Sqr(A.x-B.x)+Sqr(A.y-B.y));}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int Kirchoff(){
	int Ans=1;
	for(int i=1;i<n;i++){
		int t=0;
		for(int j=i;j<n;j++)if(a[j][i]){t=i;break;}
		if(!t)return -1;
		if(t!=i){swap(a[i],a[t]);Ans=Mod-Ans;}
		int Inv=Pow(a[i][i],Mod-2);
		for(int j=i+1;j<n;j++){
			int dlt=1ll*a[j][i]*Inv%Mod;
			for(int k=i;k<n;k++)a[j][k]=(a[j][k]-1ll*a[i][k]*dlt%Mod+Mod)%Mod;
		}
		Ans=1ll*Ans*a[i][i]%Mod;
	}
	return Ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();R=read();
		for(int i=1;i<=n;i++){
			P[i].x=read();
			P[i].y=read();
		}
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				d[i][j]=d[j][i]=Dist(P[i],P[j]);
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(d[i][j]<=R){
					bool flag=true;
					for(int k=1;k<=n;k++){
						if(k==i||k==j)continue;
						if(fabs(d[i][k]+d[k][j]-d[i][j])<eps){flag=false;break;}
					}
					if(flag){a[i][i]++;a[j][j]++;a[i][j]--;a[j][i]--;}
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=(a[i][j]%Mod+Mod)%Mod;
			}
		}
		printf("%d\n",Kirchoff());
	}
	return 0;
}