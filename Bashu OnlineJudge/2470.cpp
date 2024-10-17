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
int n,m;
char s[N][N];
int vis1[N][N],vis2[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++){
		int lst=0;
		for(int j=1;j<=m;j++){
			if(s[i][j]=='T'){
				if(!lst)lst=j;
				else{
					for(int k=lst;k<j;k++)vis1[i][k]=1;
					lst=0;
				}
			}
		}
	}
	for(int j=1;j<=m;j++){
		int lst=0;
		for(int i=1;i<=n;i++){
			if(s[i][j]=='T'){
				if(!lst)lst=i;
				else{
					for(int k=lst;k<i;k++)vis2[k][j]=1;
					lst=0;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf("o");
			if(vis1[i][j])printf("-");
			else printf(" ");
		}
		printf("\n");
		for(int j=1;j<=m;j++){
			if(vis2[i][j])printf("| ");
			else printf("  ");
		}
		printf("\n");
	}
	return 0;
}