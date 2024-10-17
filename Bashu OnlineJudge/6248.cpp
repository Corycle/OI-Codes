#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Max;
int a[N][N],cnt[N],id[N];
double Sqr(double x){return x*x;}
bool DFS(int x,int num){
	int t=0;id[num]=x;
	if(num>Max){Max=num;return true;}
	for(int y=x+1;y<=n;y++){
		if(a[x][y]){
			if(num+cnt[y]<=Max)continue;
			for(t=1;t<=num;t++){
				if(!a[id[t]][y])break;
			}
			if(t>num&&DFS(y,num+1))return true;
		}
	}
	return false;
}
int Solve(){
	for(int i=n;i>=1;i--){
		DFS(i,1);
		cnt[i]=Max;
	}
	return Max;
}
int main(){
//	freopen("graph.in","r",stdin);
//	freopen("graph.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=read();
		}
	}
	int num=Solve();
	double ans=0;
	if(cnt){
		double v=(double)m/num;
		ans=num*(num-1)/2*Sqr(v);
	}
	printf("%.10lf",ans);
	return 0;
}