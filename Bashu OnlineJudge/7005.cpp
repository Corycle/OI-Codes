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
const ll INF=0x3f3f3f3f3f3f3f3f;
const int inf=0x3f3f3f3f;
const int M=405;
const int N=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll f[2][N][N][N];
int n,m,Ans,a[M],b[M];
int P(int x){return x>n?x-n:x;}
int main(){
//	freopen("stamps.in","r",stdin);
//	freopen("stamps.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	a[++n]=m;
	for(int i=1;i<=n;i++){a[i+n]=a[i]+a[n];b[i+n]=b[i];}
	memset(f,0x3f,sizeof(f));
	f[0][n][n][0]=f[1][n][n][0]=0;
	for(int t=2;t<=n;t++){
		for(int l=n;l+t-1>=n;l--){
			int r=l+t-1,L=P(l),R=P(r);
			f[0][L][R][0]=abs(m-a[l]);
			f[1][L][R][0]=abs(m-a[r]);
			for(int k=1;k<=t;k++){
				ll dlt=0;
				int FL=P(l+1),FR=P(r-1);
				f[0][L][R][k]=min(f[0][L][R][k],min(f[0][FL][R][k]+abs(a[l]-a[l+1]),f[1][FL][R][k]+abs(a[l]-a[r])));
				f[1][L][R][k]=min(f[1][L][R][k],min(f[1][L][FR][k]+abs(a[r]-a[r-1]),f[0][L][FR][k]+abs(a[r]-a[l])));
				dlt=min(f[0][FL][R][k-1]+abs(a[l]-a[l+1]),f[1][FL][R][k-1]+abs(a[l]-a[r]));if(dlt<=b[l])f[0][L][R][k]=min(f[0][L][R][k],dlt);
				dlt=min(f[1][L][FR][k-1]+abs(a[r]-a[r-1]),f[0][L][FR][k-1]+abs(a[r]-a[l]));if(dlt<=b[r])f[1][L][R][k]=min(f[1][L][R][k],dlt);
				if(f[0][L][R][k]!=INF)Ans=max(Ans,k);
				if(f[1][L][R][k]!=INF)Ans=max(Ans,k);
			}
		}
	}
	printf("%d\n",Ans);
	return 0;
}