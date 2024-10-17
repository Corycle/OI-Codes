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
const int Mod=12;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Matrix{
	int a[2][2];
	void Init(){a[0][0]=a[0][1]=a[1][0]=a[1][1]=0;}
	void E(){Init();a[0][0]=a[1][1]=1;}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				for(int k=0;k<2;k++){
					C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j]%Mod)%Mod;
				}
			}
		}
		return C;
	}
};
int n;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(scanf("%d",&n)!=EOF){
		Matrix ans,x;ans.E();x.Init();
		x.a[0][0]=x.a[0][1]=x.a[1][0]=1;
		n-=2;
		while(n){
			if(n&1)ans=ans*x;
			x=x*x;n>>=1;
		}
		int t=(ans.a[0][0]+ans.a[0][1])%Mod;
		if(t==0){printf("YES\n");continue;}
		if(t%3==0){printf("3\n");continue;}
		if(t%4==0){printf("4\n");continue;}
		printf("NO\n");
	}
	return 0;
}