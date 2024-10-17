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
const double eps=1e-15;
const int N=105;
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
	if(abs(a[x][x])<eps)return;
	for(int i=x+1;i<=n;i++){
		p=a[i][x]/a[x][x];
		for(int j=x;j<=n+1;j++){
			a[i][j]-=p*a[x][j];
		}
	}
}
void Gauss(){
	for(int i=1;i<=n;i++)Deal(i);
	//神  仙
	int flag1=0,flag2=0;
	for(int i=1;i<=n;i++){
		int j=1;
		while(abs(a[i][j])<eps&&j<=n+1)j++;
		if(j>n+1)flag1=1;
		else if(j==n+1)flag2=1;
	}
	if(flag2){printf("-1");exit(0);}
	if(flag1){printf("0");exit(0);}
	//保  佑 
	for(int i=n;i>=1;i--){
		for(int j=n;j>i;j--)a[i][n+1]-=a[i][j]*ans[j];
		if(abs(a[i][i])<eps){
			if(abs(a[i][n+1])<eps)printf("0");
			if(abs(a[i][n+1])>eps)printf("-1");
			exit(0);
		}
		ans[i]=a[i][n+1]/a[i][i];
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n+1;j++){
			a[i][j]=read();
		}
	}
	Gauss();
	for(int i=1;i<=n;i++){
		printf("x%d=",i);
		if(abs(ans[i])<eps)printf("0\n");
		else printf("%.2lf\n",ans[i]);
	}
	return 0;
}