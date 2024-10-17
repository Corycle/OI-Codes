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
const int N=100005;
const int B=1000;
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int a[N],h[N],id[N],fa[N],f[N][M],sum[N];
struct edge{int to,next;}d[N];
struct Node{int op,x,y,ans;}Q[N];
int Belong(int x){return (x-1)/B;}
bool cmp(int x,int y){return a[x]<a[y];}
int Find(int x){return x==fa[x]?x:Find(fa[x]);}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Insert(int p){
	int &x=Q[p].x,&y=Q[p].y;
	x=Find(x);y=Find(y);
	if(x==y)return;
	if(sum[x]>sum[y])swap(x,y);
	fa[x]=y;sum[y]+=sum[x];
	for(int i=0;i<=Belong(n);i++)f[y][i]+=f[x][i];
}
void Delete(int p){
	int &x=Q[p].x,&y=Q[p].y;
	if(x==y)return;
	fa[x]=x;sum[y]-=sum[x];
	for(int i=0;i<=Belong(n);i++)f[y][i]-=f[x][i];
}
int Query(int p){
	int x=Find(Q[p].x),k=Q[p].y;
	for(int i=0;i<=Belong(n);i++){
		if(k>f[x][i])k-=f[x][i];
		else{
			for(int j=i*B+1;j<=min(n,(i+1)*B);j++){
				if(Find(id[j])!=x)continue;
				if(!(--k))return a[id[j]];
			}
		}
	}
	return -1;
}
void DFS(int x){
	if(Q[x].op==1)Insert(x);
	if(Q[x].op==3)Q[x].ans=Query(x);
	for(int i=h[x];i;i=d[i].next)DFS(d[i].to);
	if(Q[x].op==1)Delete(x);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)fa[i]=id[i]=i;
	sort(id+1,id+n+1,cmp);
	for(int i=1;i<=n;i++)sum[i]=f[id[i]][Belong(i)]=1;
	for(int i=1;i<=m;i++){
		int op=read();
		if(op==1){int x=read(),y=read();Add(i-1,i);Q[i]=(Node){op,x,y,0};}
		if(op==2){int x=read();Add(x,i);Q[i]=(Node){op,x,0,0};}
		if(op==3){int x=read(),y=read();Add(i-1,i);Q[i]=(Node){op,x,y,0};}
	}
	DFS(0);
	for(int i=1;i<=m;i++){
		if(Q[i].op==3)printf("%d\n",Q[i].ans);
	}
	return 0;
}