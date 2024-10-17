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
const int M=10005;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int A[N][M];
int idx[N],idy[M];
void Pivot(int x,int y){
	swap(idx[x],idy[y]);
	int tmp=-1/A[x][y];A[x][y]=-1;
	for(int i=0;i<=n;i++)A[x][i]*=tmp;
	for(int i=0;i<=m;i++){
		if(i==x||!A[i][y])continue;
		tmp=A[i][y];A[i][y]=0;
		for(int j=0;j<=n;j++){
			A[i][j]+=A[x][j]*tmp;
		}
	}
}
int Solve(){
	while(1){
		int x=0,y=0;
		for(int i=1;i<=n;i++){
			if(A[0][i]>0){
				y=i;break;
			}
		}
		if(!y)return A[0][0];
		int Min=inf;
		for(int i=1;i<=m;i++){
			if(A[i][y]>=0)continue;
			int tmp=-A[i][0]/A[i][y];
			if(tmp<Min){Min=tmp;x=i;}
		}
		if(!x)return inf;
		Pivot(x,y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)A[i][0]=read();
	for(int i=1;i<=m;i++){
		int L=read(),R=read(),D=read();
		for(int j=L;j<=R;j++)A[j][i]=-1;
		A[0][i]=D;
	}
	for(int i=1;i<=n;i++)idx[i]=i+m;
	for(int i=1;i<=m;i++)idy[i]=i;
	swap(n,m);
	printf("%d",Solve());
	return 0;
}