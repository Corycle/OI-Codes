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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int s[N],sg[N];
int DFS(int x){
	if(sg[x]>=0)return sg[x];
	int g[N];
	memset(g,0,sizeof(g));
	for(int i=1;i<=n;i++){
		if(x<s[i])continue;
		g[DFS(x-s[i])]=1;
	}
	for(int i=0;;i++){
		if(!g[i])return sg[x]=i;
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(1){
		n=read();if(!n)break;
		memset(sg,-1,sizeof(sg));
		for(int i=1;i<=n;i++)s[i]=read();
		m=read();sg[0]=0;
		while(m--){
			int sum=0,num=read();
			for(int i=1;i<=num;i++){
				sum^=DFS(read());
			}
			if(sum)printf("W");
			else printf("L");
		}
		printf("\n");
	}
	return 0;
}