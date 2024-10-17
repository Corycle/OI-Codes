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
const int Mod=1e9+7;
const int N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll K;
char s[N][N];
int n,m,cnt,tot1,tot2,num1,num2;
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,ll y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
}
struct Matrix{
	int a[2][2];
	void Clear(){memset(a,0,sizeof(a));}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Clear();
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				for(int k=0;k<2;k++){
					C.a[i][j]=mod(C.a[i][j]+1ll*A.a[i][k]*B.a[k][j]%Mod);
				}
			}
		}
		return C;
	}
}A,B;
void Solve(ll t){B=A;while(t){if(t&1)B=B*A;A=A*A;t>>=1;}}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++){
			cnt+=(s[i][j]=='#');
			if(i)tot1+=(s[i][j]=='#'&&s[i-1][j]=='#');
			if(j)tot2+=(s[i][j]=='#'&&s[i][j-1]=='#');
		}
	}
	for(int i=1;i<=m;i++)num1+=(s[1][i]=='#'&&s[n][i]=='#');
	for(int i=1;i<=n;i++)num2+=(s[i][1]=='#'&&s[i][m]=='#');
	if((num1&&num2)||K<=1){puts("1");return 0;}
	if(!num1&&!num2){printf("%d\n",Pow(cnt,K-1));return 0;}
	int tot=(num1?tot1:tot2),num=(num1?num1:num2);
	A.a[0][0]=cnt;A.a[0][1]=Mod-tot;A.a[1][1]=num;Solve(K-2);
	printf("%d\n",mod(B.a[0][0]+B.a[0][1]));
	return 0;
}
