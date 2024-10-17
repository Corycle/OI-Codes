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
const int M=20005;
const int N=605;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Mod,f[N][N],g[N][N];
struct Point{
	int x,y;
	friend Point operator-(Point A,Point B){return (Point){A.x-B.x,A.y-B.y};}
	friend int operator^(Point A,Point B){return A.x*B.y-A.y*B.x;}
}P1[N],P2[M],O;
int mod(int x){return x>=Mod?x-Mod:x;}
int Cross(Point A,Point B,Point C){return (A-C)^(B-C);}
bool cmp(Point A,Point B){return Cross(A,B,O)<0;}
void Solve(int x){
	int num=0;
	O=P1[x];sort(P2+1,P2+m+1,cmp);
	for(int i=2,p=1;i<=n-2;i++){
		int y=(x+i)%n,flag=0;if(!y)y=n;
		while(p<=m&&Cross(P1[x],P1[y],P2[p])>=0){
			if(!Cross(P1[x],P1[y],P2[p]))flag=1;
			num++;p++;
		}
		if(!flag)g[x][y]=(num&1)^1;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Mod=read();
	for(int i=1;i<=n;i++){P1[i].x=read();P1[i].y=read();}
	for(int i=1;i<=m;i++){P2[i].x=read();P2[i].y=read();}
	for(int i=1;i<=n;i++)Solve(i);
	for(int i=1;i<n;i++)f[i][i+1]=1;
	for(int i=1;i<=n;i++)g[i][i%n+1]=g[i%n+1][i]=1;
	for(int t=3;t<=n;t++){
		for(int i=1;i+t-1<=n;i++){
			int j=i+t-1;
			if(!g[i][j])continue;
			for(int k=i+1;k<=j-1;k++){
				f[i][j]=mod(f[i][j]+1ll*f[i][k]*f[k][j]%Mod);
			}
		}
	}
	printf("%d\n",f[1][n]);
	return 0;
}
