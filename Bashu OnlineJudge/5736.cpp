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
const int N=10;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<int,int>D,L;
int n,m,Ans[N][N];
int a[N][N],b[N][N],c[N][N];
int dx[N]={1,1,1,-1,-1,-1,0,0};
int dy[N]={-1,0,1,-1,0,1,-1,1};
int Calc(int x,int y){
	int num=0;
	for(int i=0;i<8;i++){
		int fx=x+dx[i],fy=y+dy[i];
		if(fx<1||fx>n||fy<1||fy>m)continue;
		num+=b[fx][fy];
	}
	if(b[x][y]==1&&(num==2||num==3))return 1;
	if(b[x][y]==0&&num==3)return 1;
	return 0;
}
int GetHash(int a[][N]){
	int sta=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			sta=sta<<1|a[i][j];
		}
	}
	return sta;
}
void Check(int n,int m){
	int T=60,flag=0;
	int Hash=GetHash(a);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)b[i][j]=a[i][j];
	while(T--){
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)c[i][j]=Calc(i,j);
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)b[i][j]=c[i][j];
		int tmp=GetHash(b);
		if(D[tmp]){D[Hash]=1;return;}
		if(L[tmp]){L[Hash]=1;Ans[n][m]++;return;}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)flag|=b[i][j];
	T=60;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)b[i][j]=a[i][j];
	while(T--){
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)c[i][j]=Calc(i,j);
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)b[i][j]=c[i][j];
		int tmp=GetHash(b);
		if(!flag)D[tmp]=1;
		else L[tmp]=1;
	}
	if(flag)L[Hash]=1;else D[Hash]=1;
	Ans[n][m]+=flag;
}
void DFS(int x,int y){
	if(y>m){DFS(x+1,1);return;}
	if(x>n){Check(n,m);return;}
	a[x][y]=0;DFS(x,y+1);
	a[x][y]=1;DFS(x,y+1);
}
void GetAns(){
	for(int i=1;i<=5;i++){
		for(int j=i;j<=5;j++){
			L.clear();D.clear();
			n=i;m=j;DFS(1,1);
			Ans[j][i]=Ans[i][j];
			cout<<"Ans: "<<i<<" "<<j<<" = "<<Ans[i][j]<<endl;
		}
	}
	exit(0);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
//	GetAns();
	int T=read();
	while(T--){
		n=read();m=read();
		if(n>m)swap(n,m);
		if(n==1)puts("0");
		
		if(n==2&&m==2)puts("5");
		if(n==2&&m==3)puts("18");
		if(n==2&&m==4)puts("73");
		if(n==2&&m==5)puts("267");
		
		if(n==3&&m==3)puts("150");
		if(n==3&&m==4)puts("1533");
		if(n==3&&m==5)puts("11398");
		
		if(n==4&&m==4)puts("31828");
		if(n==4&&m==5)puts("469972");
		
		if(n==5&&m==5)puts("12785753");
	}
	return 0;
}