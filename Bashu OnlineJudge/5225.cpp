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
const int Mod=1e4+7;
const int N=205;
const int M=305;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,K,tot,id1[N],id2[N],f[N][N][N],g[N];
int mod(int x){return x>=Mod?x-Mod:x;}
struct Matrix{
	int a[M][M];
	void Init(){for(int i=0;i<=tot;i++)for(int j=0;j<=tot;j++)a[i][j]=0;}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(int i=0;i<=tot;i++){
			for(int k=i;k<=tot;k++){
				for(int j=k;j<=tot;j++){
					C.a[i][j]=mod(C.a[i][j]+A.a[i][k]*B.a[k][j]%Mod);
				}
			}
		}
		return C;
	}
};
Matrix A,Ans;
void Prepare(){
	f[1][n][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=n;j>=i;j--){
			for(int k=0;k<=n;k++){
				if(s[i]==s[j])f[i+1][j-1][k]=mod(f[i+1][j-1][k]+f[i][j][k]);
				else{
					f[i+1][j][k+1]=mod(f[i+1][j][k+1]+f[i][j][k]);
					f[i][j-1][k+1]=mod(f[i][j-1][k+1]+f[i][j][k]);
				}
			}
		}
	}
}
void GetG(int type){
	memset(g,0,sizeof(g));
	if(type){
		for(int i=1;i<=n;i++){
			for(int j=i;j<=i+1;j++){
				if(s[i]==s[j])for(int k=0;k<=n;k++)g[k]=mod(g[k]+f[i][j][k]);
			}
		}
	}
	else{
		for(int i=1;i<=n;i++){
			if(s[i]==s[i+1])for(int k=0;k<=n;k++)g[k]=mod(g[k]+f[i][i+1][k]);
		}
	}
}
int Solve(int type,int t){
	GetG(type);A.Init();
	int m=(n+1)/2;tot=0;
	for(int i=1;i<=n;i++){id1[i]=++tot;A.a[tot][tot]=24;}
	for(int i=m;i>=1;i--){id2[i]=++tot;A.a[tot][tot]=25;}
	int T=++tot;A.a[T][T]=type*26;A.a[id2[1]][T]=1;
	for(int i=1;i<n;i++)A.a[id1[i]][id1[i+1]]=1;
	for(int i=1;i<m;i++)A.a[id2[i+1]][id2[i]]=1;
	for(int i=1;i<=n;i++)A.a[id1[i]][id2[(n-i+1)/2]]=g[i];
//	for(int i=0;i<=n;i++)cout<<g[i]<<" ";cout<<endl;
//	for(int i=0;i<=tot;i++){
//		for(int j=0;j<=tot;j++)cout<<A.a[i][j]<<" ";cout<<endl;
//	}
	Ans.Init();Ans.a[0][1]=1;Ans.a[0][id2[m]]=g[0];
	while(t){if(t&1)Ans=Ans*A;A=A*A;t>>=1;}
	return Ans.a[0][T];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);K=read();Prepare();
	if((n+K)%2==0)printf("%d",Solve(1,(n+K)/2));
	if((n+K)%2==1)printf("%d",mod(Solve(1,(n+K+1)/2)-Solve(0,(n+K+1)/2)+Mod));
	return 0;
}