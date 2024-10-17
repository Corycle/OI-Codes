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
const int N=4e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>P;
int n,m,num,cnt=1;
int h[N],deg[N],vis[N*2];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(int x){
	for(int &i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[i])continue;
		vis[i]=vis[i^1]=1;DFS(y);num++;
		if(num%2==0)printf("%d %d\n",x,y);
		if(num%2==1)printf("%d %d\n",y,x);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
		deg[x]++;deg[y]++;
	}
	for(int i=1;i<=n;i++)if(deg[i]&1)P.push_back(i);
	for(int i=0;i<P.size();i+=2){
		Add(P[i],P[i+1]);Add(P[i+1],P[i]);
		deg[P[i]]++;deg[P[i+1]]++;m++;
	}
	if(m&1){Add(1,1);Add(1,1);m++;}
	printf("%d\n",m);
	DFS(1);
	return 0;
}
