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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
char s[N][N],a[N][N],b[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++)a[i][j]=b[i][j]='.';a[i][1]=b[i][m]='#';
		for(int j=2;j<m;j++)if(i&1)a[i][j]='#';else b[i][j]='#';
		for(int j=1;j<=m;j++)if(s[i][j]=='#')a[i][j]=b[i][j]='#';
	}
	for(int i=1;i<=n;i++)printf("%s\n",a[i]+1);puts("");
	for(int i=1;i<=n;i++)printf("%s\n",b[i]+1);puts("");
	return 0;
}
