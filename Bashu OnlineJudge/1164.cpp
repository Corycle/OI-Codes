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
const int M=1000005;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,S,T,id[M];
struct Matrix{
	int n,m,a[N][N];
	void Clean(){
		n=m=0;
		memset(a,0,sizeof(a));
	}
}F,G;
Matrix Multi(Matrix A,Matrix B){
	Matrix C;
	C.n=A.n;C.m=B.m;
	memset(C.a,0x3f,sizeof(C.a));
	for(int i=1;i<=C.n;i++){
		for(int j=1;j<=C.m;j++){
			for(int k=1;k<=A.m;k++){
				C.a[i][j]=min(C.a[i][j],A.a[i][k]+B.a[k][j]);
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
	p=read();m=read();
	S=read();T=read();
	memset(F.a,0x3f,sizeof(F.a));
	memset(G.a,0x3f,sizeof(G.a));
	for(int i=1;i<=m;i++){
		int dis=read(),x=read(),y=read();
		if(!id[x])id[x]=++n;
		if(!id[y])id[y]=++n;
		G.a[id[x]][id[y]]=dis;
		G.a[id[y]][id[x]]=dis;
	}
	for(int i=1;i<=n;i++)F.a[i][i]=0;
	G.n=G.m=F.n=F.m=n;
	Matrix ans=Pow(F,G,p);
	printf("%d",ans.a[id[S]][id[T]]);
	return 0;
}