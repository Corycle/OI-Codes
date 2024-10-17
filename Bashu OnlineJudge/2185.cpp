#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double a[N][N],ans[N];
void Deal(int x){
	int k=x;
	double p=0,Max=abs(a[x][x]);
	for(int i=x+1;i<=n;i++){
		if(abs(a[i][x])>Max){
			Max=abs(a[i][x]);k=i;
		}
	}
	for(int i=x;i<=n+1;i++){
		swap(a[x][i],a[k][i]);
	}
	for(int i=x+1;i<=n;i++){
		p=a[i][x]/a[x][x];
		for(int j=x;j<=n+1;j++){
			a[i][j]-=p*a[x][j];
		}
	}
}
void Gauss(){
	for(int i=1;i<=n;i++)Deal(i);
	for(int i=n;i>=1;i--){
		for(int j=n;j>i;j--)a[i][n+1]-=a[i][j]*ans[j];
		ans[i]=a[i][n+1]/a[i][i];
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read()+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<n;j++){
			scanf("%lf",&a[i][j]);
			a[i][n+1]-=a[i][j]*a[i][j];
			a[i][j]=-a[i][j]*2;
			a[i][n]=1;
		}
	}
	Gauss();
	for(int i=1;i<n;i++){
		printf("%.3lf ",ans[i]);
	}
	return 0;
}