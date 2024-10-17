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
int n;
int g[N][N],sg[N];
int DFS(int x){
	if(x<0)return 0;
	if(sg[x]>=0)return sg[x];
	for(int i=1;i<=x;i++){
		g[x][DFS(i-3)^DFS(x-i-2)]=1;
	}
	for(int i=0;i<=x;i++){
		if(!g[x][i])return sg[x]=i;
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	memset(sg,-1,sizeof(sg));
	if(DFS(n))printf("1");
	else printf("2");
	return 0;
}