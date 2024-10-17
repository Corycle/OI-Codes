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
const int N=40;
inline int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
int a[N][N],f[N][N];
inline int A(int x,int y){return f[x][y]?-a[x][y]:a[x][y];}
inline int Solve2(int x,int y,int val){
	f[x][y]=val;
	f[x+m][y]=f[m][y]^val;
	f[x][y+m]=f[x][m]^val;
	f[x+m][y+m]=f[x+m][y]^f[x+m][m];
	return A(x,y)+A(x+m,y)+A(x,y+m)+A(x+m,y+m);
}
inline int Solve1(int y,int val){
	f[m][y]=val;
	f[m][y+m]=f[m][y]^f[m][m];
	int ans=A(m,y)+A(m,y+m);
	for(int i=1;i<m;i++)ans+=max(Solve2(i,y,0),Solve2(i,y,1));
	return ans;
}
inline int Calc(){
	int ans=0;
	for(int i=1;i<=n;i++)ans+=A(i,m);
	for(int i=1;i<m;i++)ans+=max(Solve1(i,0),Solve1(i,1));
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=(n+1)>>1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=read();
			Ans+=a[i][j];
		}
	}
	for(int i=0;i<(1<<m);i++){
		for(int j=1;j<=m;j++)f[j][m]=(i>>(j-1))&1;
		for(int j=1;j<m;j++)f[j+m][m]=f[j][m]^f[m][m];
		Ans=max(Ans,Calc());
	}
	printf("%d",Ans);
	return 0;
}