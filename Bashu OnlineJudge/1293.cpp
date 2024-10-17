#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
using namespace std;
int main(){
//	freopen("t1.in","r",stdin);
//	freopen("t1.out","w",stdout);
	int n,i,j,x,y,s=0;
	cin>>n>>i>>j;
	int a[n+1][n+1],b[n+1][n+1];
	for(x=1;x<=n;x++)
		for(y=1;y<=n;y++)
		{	a[x][y]=x;b[x][y]=y;}
	for(x=1;x<=n;x++)printf("(%d,%d)",a[i][x],b[i][x]);printf("\n");
	for(x=1;x<=n;x++)printf("(%d,%d)",a[x][j],b[x][j]);printf("\n");
	for(x=i,y=j;x!=1&&y!=1;x--,y--)s++;
	for(x,y;x<=n&&y<=n;x++,y++)
		printf("(%d,%d)",x,y);printf("\n");
	for(x=i,y=j;x!=1&&y!=n;x--,y++)s--;
	for(x,y;x<=n&&y>=1;x++,y--)
		printf("(%d,%d)",y,x);
	return 0;
}