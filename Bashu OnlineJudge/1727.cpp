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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,fx,fy,a[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++)a[i][j]=(s[j]=='L');
	}
	for(int i=1;i<=n;i++){
		if(a[1][i])for(int j=1;j<=n;j++)a[j][i]^=1;
	}
	for(int i=1;i<=n;i++){
		if(a[i][1])for(int j=1;j<=n;j++)a[i][j]^=1;
	}
	/*========Type 1========*/
	int flag=1;
	for(int i=2;i<=n;i++){
		for(int j=2;j<=n;j++)if(!a[i][j])flag=0;
	}
	if(flag){printf("1 1");return 0;}
	/*========Type 2========*/
	for(int i=2;i<=n;i++){
		flag=1;
		for(int j=2;j<=n;j++)if(!a[j][i])flag=0;
		if(flag){printf("1 %d",i);return 0;}
	}
	for(int i=2;i<=n;i++){
		flag=1;
		for(int j=2;j<=n;j++)if(!a[i][j])flag=0;
		if(flag){printf("%d 1",i);return 0;}
	}
	/*========Type 3========*/
	int sum=0;
	for(int i=2;i<=n;i++){
		for(int j=2;j<=n;j++){
			if(a[i][j]){fx=i;fy=j;sum++;}
		}
	}
	if(sum==1)printf("%d %d",fx,fy);
	else printf("-1");
	return 0;
}