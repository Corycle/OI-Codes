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
int n,m,cnt;
int h[N],c[N],lstX[N],lstY[N];
struct edge{int to,next;}d[N*4];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};h[x]=cnt;
}
bool DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!c[y]){
			c[y]=3-c[x];
			if(!DFS(y))return false;
		}
		if(c[x]==c[y])return false;
	}
	return true;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		if(lstX[x]){Add(i,lstX[x]);Add(lstX[x],i);lstX[x]=0;}
		else lstX[x]=i;
		if(lstY[y]){Add(i,lstY[y]);Add(lstY[y],i);lstY[y]=0;}
		else lstY[y]=i;
	}
	for(int i=1;i<=n;i++){
		if(!c[i]){c[i]=1;if(!DFS(i)){puts("-1");return 0;};}
	}
	for(int i=1;i<=n;i++)printf("%c",(c[i]==1?'b':'r'));
	return 0;
}
