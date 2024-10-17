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
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt,Ans;
int h[N],a[N],fa[N],f1[N],f2[N],g1[N],g2[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS1(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS1(y);
		if(f1[x]<=f1[y]+1){
			f2[x]=f1[x];g2[x]=g1[x];
			f1[x]=f1[y]+1;g1[x]=y;
		}
		else if(f2[x]<=f1[y]+1){
			f2[x]=f1[y]+1;g2[x]=y;
		}
	}
	Ans=max(Ans,a[x]*f1[x]);
}
void DFS2(int x,int Max){
	Ans=max(Ans,a[x]*Max);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		if(y!=g1[x])DFS2(y,max(Max,f1[x])+1);
		else DFS2(y,max(Max,f2[x])+1);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1);DFS2(1,0);
	printf("%d",Ans);
	return 0;
}
