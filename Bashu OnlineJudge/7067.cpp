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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,X1,Y1,X2,Y2;
int main(){
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	n=read();m=read();X1=read();Y1=read();X2=read();Y2=read();
	if(abs(X1-X2)+abs(Y1-Y2)==1){puts("-1");return 0;}
	if(max(n-X2,X2-1)<=1&&max(m-Y2,Y2-1)<=1){puts("1");return 0;}
//	if(min(n,m)==1||((X2==1||X2==n)&&(Y2==1||Y2==m))){puts("2");return 0;}
	if(min(n,m)<=2||max(min(X2-1,n-X2),min(Y2-1,m-Y2))<=1){
		if(m<=3&&max(Y2-1,m-Y2)<=1&&(X2<=2||X2>=n-1)){puts("2");return 0;}
		if(n<=3&&max(X2-1,n-X2)<=1&&(Y2<=2||Y2>=m-1)){puts("2");return 0;}
		if(max(abs(X1-X2),abs(Y1-Y2))<=1){puts("3");return 0;}
		puts("2");
		return 0;
	}
	puts("3");
	return 0;
}