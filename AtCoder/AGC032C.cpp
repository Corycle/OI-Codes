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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,A,B,num,deg[N],vis[N];
void DFS(int x){
	vis[x]=1;
	for(auto y:G[x]){
		if(vis[y]==2){if(!A)A=y;else B=y;}
		if(!vis[y])DFS(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);deg[x]++;deg[y]++;}
	for(int i=1;i<=n;i++)if(deg[i]&1){puts("No");return 0;}
	for(int i=1;i<=n;i++)if(deg[i]>=6){puts("Yes");return 0;}
	for(int i=1;i<=m;i++)if(deg[i]==4)num++;
	if(num==1){puts("No");return 0;}
	if(num==2){
		int flag=0;
		for(int i=1;i<=n;i++)if(deg[i]==4)vis[i]=2;
		for(int i=1;i<=n;i++)if(!vis[i]){A=B=0;DFS(i);flag|=(A==B);}
		puts(flag?"Yes":"No");
		return 0;
	}
	if(num>=3){puts("Yes");return 0;}
	puts("No");
	return 0;
}
