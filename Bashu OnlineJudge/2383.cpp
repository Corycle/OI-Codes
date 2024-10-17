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
char s[N][N];
int sum[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++){
			if(s[i][j]=='1')sum[i][j]=sum[i][j-1]+1;
			if(s[i][j]=='0')sum[i][j]=sum[i][j-1]-1;
		}
	}
	int Max=0;
	for(int l=1;l<=m;l++){
		for(int r=l;r<=m;r++){
			int Sum=0;
			for(int i=1;i<=n;i++){
				Sum+=sum[i][r]-sum[i][l-1];
				Max=max(Max,Sum);
				Sum=max(Sum,0);
			}
		}
	}
	printf("%d",Max);
	return 0;
}