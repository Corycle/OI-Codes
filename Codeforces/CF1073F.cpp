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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int h[N],L[N],dep[N];
int n,m,A,B,C,D,sum,cnt,Max;
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x,int fa,int depth){
	int num=0,son=0;dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;DFS(y,x,depth+1);num++;
		if(dep[L[y]]>dep[L[x]]){son=L[x];L[x]=L[y];}
		else if(dep[L[y]]>dep[son])son=L[y];
	}
	if(num==0)L[x]=x;
	if(num>1&&(dep[x]>dep[Max]||(dep[x]==dep[Max]&&dep[L[x]]+dep[son]>sum))){Max=x;sum=dep[L[x]]+dep[son];}
}
void Solve(int x){
	int num=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dep[y]>dep[x]){num++;Solve(d[i].to);}
	}
	if(!num){if(dep[A]<dep[x]){B=A;A=x;}else if(dep[B]<dep[x])B=x;}
}
int main(){
	n=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	DFS(1,0,1);int x=Max;Solve(x);
	C=A;D=B;A=0;B=0;Max=sum=0;
	DFS(x,0,1);int y=Max;Solve(y);
	printf("%d %d\n%d %d\n",A,C,B,D);
	return 0;
}
