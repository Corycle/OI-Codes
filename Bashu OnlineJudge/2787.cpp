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
const double eps=1e-5;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double a[N][N];
bool pd(double x){
	return abs(x)<eps;
}
double Det(){
	int flag=0;
	double ans=1;
	for(int i=1;i<=n;i++){
		if(pd(a[i][i])){
			int j;
			for(j=i+1;j<=n;j++){
				if(!pd(a[j][i]))break;
			}
			if(j==n+1)return 0;
			for(int k=i;k<=n;k++)swap(a[i][k],a[j][k]);
			flag++;
		}
		ans*=a[i][i];
		for(int k=i+1;k<=n;k++)a[i][k]/=a[i][i];
		for(int j=i+1;j<=n;j++){
			for(int k=i+1;k<=n;k++){
				a[j][k]-=a[j][i]*a[i][k];
			}
		}
	}
	if(flag&1)return -ans;
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		a[x][y]=a[y][x]=-1;
		a[x][x]++;a[y][y]++;
	}
	n--;
	printf("%.0lf",Det());
	return 0;
}