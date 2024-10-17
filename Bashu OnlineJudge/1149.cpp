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
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,minn,maxx,a[N],g[N];
int f[N][N],s[N][N],s2[N][N];
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i+n]=a[i]=read();
	for(int i=1;i<=n*2;i++){
		g[i]=g[i-1]+a[i];
		f[i][i]=0;
		s[i][i]=i;
	}
	for(int t=2;t<=n;t++){
		for(int i=1;i<=2*n-t+1;i++){
			int j=i+t-1;
			f[i][j]=inf;
			for(int k=s[i][j-1];k<=s[i+1][j];k++){
				if(f[i][j]>f[i][k-1]+f[k][j]){
					f[i][j]=f[i][k-1]+f[k][j];
					s[i][j]=k;
				}
			}
			f[i][j]+=g[j]-g[i-1];
    	}
	}
	minn=inf,maxx=0;
	for(int i=1;i<=n;i++){
		minn=min(minn,f[i][i+n-1]);
	}
	for(int t=2;t<=n;t++){
		for(int i=1;i<=2*n-t+1;i++){
			int j=i+t-1;
			f[i][j]=max(f[i+1][j],f[i][j-1]);
			f[i][j]+=g[j]-g[i-1];
    	}
	}
	for(int i=1;i<=n;i++){
		maxx=max(maxx,f[i][i+n-1]);
	}
	printf("%d\n%d",minn,maxx);
	return 0;
}