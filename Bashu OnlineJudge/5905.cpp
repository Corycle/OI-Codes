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
const int N=500005;
int read(){
	int s=0,f1=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f1=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f1;
}
char s[N];
int n,tot,f1[N][2],f2[N][2];
int DFS(){
	int x=++tot;
	f1[x][0]=1;f2[x][0]=inf;
	f1[x][1]=0;f2[x][1]=inf;
	if(s[x]=='2'){
		int l=DFS(),r=DFS();
		f1[x][0]=max(f1[x][0],f1[l][1]+f1[r][1]+1);
		f1[x][1]=max(f1[x][1],f1[l][0]+f1[r][1]);
		f1[x][1]=max(f1[x][1],f1[l][1]+f1[r][0]);
		
		f2[x][0]=min(f2[x][0],f2[l][1]+f2[r][1]+1);
		f2[x][1]=min(f2[x][1],f2[l][0]+f2[r][1]);
		f2[x][1]=min(f2[x][1],f2[l][1]+f2[r][0]);
	}
	if(s[x]=='1'){
		int y=DFS();
		f1[x][0]=max(f1[x][0],f1[y][1]+1);
		f1[x][1]=max(f1[x][1],max(f1[y][0],f1[y][1]));
		
		f2[x][0]=min(f2[x][0],f2[y][1]+1);
		f2[x][1]=min(f2[x][1],min(f2[y][0],f2[y][1]));
	}
	if(s[x]=='0'){
		f1[x][0]=1;f1[x][1]=0;
		f2[x][0]=1;f2[x][1]=0;
	}
	return x;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	DFS();
	printf("%d ",max(f1[1][0],f1[1][1]));
	printf("%d ",min(f2[1][0],f2[1][1]));
	return 0;
}