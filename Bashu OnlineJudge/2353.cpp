#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
int n,m,t,a[305][305];
inline int read(){
	int s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s;
}
int main(){
	int i,j,k;
	n=read();m=read();t=read();
	memset(a,0xf,sizeof(a));
	for(i=1;i<=m;i++){
		int x,y,z;
		x=read();y=read();z=read();
		a[x][y]=z;
	}
	for(k=1;k<=n;k++){
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++){
				a[i][j]=min(a[i][j],max(a[i][k],a[k][j]));
			}
		}
	}
	for(i=1;i<=t;i++){
		int x,y;
		x=read();y=read();
		if(a[x][y]==a[0][0])printf("-1\n");
		else printf("%d\n",a[x][y]);
	}
	return 0;
}