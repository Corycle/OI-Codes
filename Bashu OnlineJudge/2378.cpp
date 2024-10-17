#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
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
const int Mod=2009;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
char s[N];
struct Matrix{
	ll n,m,a[N][N];
	void Clean(){
		n=m=0;
		memset(a,0,sizeof(a));
	}
}F,G;
Matrix Multi(Matrix A,Matrix B){
	Matrix C;C.Clean();
	C.n=A.n;C.m=B.m;
	for(ll i=1;i<=C.n;i++){
		for(ll j=1;j<=C.m;j++){
			for(ll k=1;k<=A.m;k++){
				C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j]%Mod)%Mod;
			}
		}
	}
	return C;
}
Matrix Pow(Matrix A,Matrix B,ll y){
	Matrix ans=A,tot=B;
	while(y){
		if(y&1)ans=Multi(ans,tot);
		tot=Multi(tot,tot);
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	F.n=F.m=G.n=G.m=n*9;
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=8;j++){
			G.a[i+j*n][i+j*n-n]=1;
		}
		for(int j=1;j<=n;j++){
			int k=s[j]-'0';
			if(k)G.a[i][j+k*n-n]=1;
		}
	}
	for(int i=1;i<=n*9;i++)F.a[i][i]=1;
	Matrix ans=Pow(F,G,m);
	printf("%d",ans.a[1][n]);
	return 0;
}