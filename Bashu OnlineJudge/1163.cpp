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
const int Mod=10000;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,c[N][N],vis[N][N];
struct Matrix{
	int n,m,a[N][N];
	void Clean(){
		n=m=0;
		memset(a,0,sizeof(a));
	}
}F,G[15];
Matrix Multi(Matrix A,Matrix B){
	Matrix C;C.Clean();
	C.n=A.n;C.m=B.m;
	for(int i=1;i<=C.n;i++){
		for(int j=1;j<=C.m;j++){
			for(int k=1;k<=A.m;k++){
				C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j]%Mod)%Mod;
			}
		}
	}
	return C;
}
Matrix Pow(Matrix A,Matrix B,int y){
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
	int S=read()+1,T=read()+1,p=read();
	for(int i=1;i<=m;i++){
		int x=read()+1,y=read()+1;
		c[x][y]=c[y][x]=1;
	}
	m=read();
	for(int t=1;t<=m;t++){
		int num=read();
		for(int i=0;i<num;i++){
			int x=read()+1;
			for(int j=i;j<12;j+=num){
				vis[j][x]=1;
			}
		}
	}
	F.n=F.m=n;
	for(int i=1;i<=n;i++)F.a[i][i]=1;
	for(int t=0;t<12;t++){
		G[t].n=G[t].m=n;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				G[t].a[i][j]=(c[i][j]&&!vis[t][j]);
			}
		}
	}
	for(int i=1;i<12;i++)F=Multi(F,G[i]);
	F=Multi(F,G[0]);
	int k=p/12,t=p-k*12;
	Matrix ans;
	ans.Clean();ans.n=ans.m=n;
	for(int i=1;i<=n;i++)ans.a[i][i]=1;
	ans=Pow(ans,F,k);
	for(int i=1;i<=t;i++)ans=Multi(ans,G[i]);
	printf("%d",ans.a[S][T]);
	return 0;
}