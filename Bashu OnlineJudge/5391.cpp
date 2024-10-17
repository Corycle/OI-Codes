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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,st,cnt,root;
int h[N],ls[N],rs[N],ch[N][2],deg[N],Min[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS1(int x,int fa){
	int num=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS1(y,x);
		ch[x][num++]=y;
		Min[x]=min(Min[x],Min[y]);
	}
}
void DFS2(int x){
	if(deg[x]==1&&x!=st)root=x;//num_son = 0
	else if((x!=st&&deg[x]==2)||(x==st&&deg[x]==1)){//num_son = 1
		if(ch[x][0]<Min[ch[x][0]])DFS2(ch[x][0]);
		else root=x;
	}
	else{//num_son = 2
		if(Min[ch[x][0]]>Min[ch[x][1]])DFS2(ch[x][0]);
		else DFS2(ch[x][1]);
	}
}
int DFS3(int x,int fa){
	if(deg[x]==1&&x!=root)return x;//num_son = 0
	int tmp=n+1;
	if((x!=root&&deg[x]==2)||(x==root&&deg[x]==1))tmp=x;//num_son = 1
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		int dlt=DFS3(y,x);
		if(dlt>tmp)rs[x]=y;
		else {rs[x]=ls[x];ls[x]=y;tmp=dlt;}
	}
	return tmp;
}
void DFS(int x){
	if(ls[x])DFS(ls[x]);
	printf("%d ",x);
	if(rs[x])DFS(rs[x]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		deg[i]=read();Min[i]=n+1;
		for(int j=1;j<=deg[i];j++)Add(i,read());
		if(deg[i]<=2){Min[i]=i;if(!st)st=i;}
	}
	DFS1(st,0);DFS2(st);DFS3(root,0);DFS(root);
	return 0;
}