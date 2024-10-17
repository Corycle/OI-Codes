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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int f[N][N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	f[0][read()]=1;m=read();
	for(int i=1;i<=n;i++){
		int x=read();
		for(int j=0;j<=m;j++){
			if(f[i-1][j]&&j+x<=m)f[i][j+x]=1;
			if(f[i-1][j]&&j-x>=0)f[i][j-x]=1;
		}
	}
	for(int i=m;i>=1;i--){
		if(f[n][i]){
			printf("%d\n",i);
			return 0;
		}
	}
	printf("-1");
	return 0;
}