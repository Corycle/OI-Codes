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
ll num;
int n,m,cnt,tot,Min,Root;
int h[N],p[N],vis[N],sum[N];
struct edge{int to,next;}d[N*2];
struct Node{int x,dis,num;}P[N];
bool cmp(Node A,Node B){return A.dis<B.dis;}
ll Sum(ll x){return x*(x-1)/2;}
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Find(int x,int fa,int Size){
	int S=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		Find(y,x,Size);
		sum[x]+=sum[y];
		S=max(S,sum[y]);
	}
	S=max(S,Size-sum[x]);
	if(S<Min){Root=x;Min=S;}
}
void DFS(int x,int fa,int dis){
	sum[x]=1;
	P[++tot]=(Node){x,dis,1};
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		DFS(y,x,dis+1);
		sum[x]+=sum[y];
	}
}
int Solve(int x){
	int l=1,r=tot,ans=0;
	while(l<=r){
		if(P[l].dis+P[r].dis<x)l++;
		else{
			if(P[l].dis+P[r].dis==x){
				if(l==r)ans+=Sum(P[l].num);
				else ans+=P[l].num*P[r].num;
			}
			r--;
		}
	}
	return ans;
}
void Calc(int x,int fa,int dis,int f){
	tot=0;DFS(x,fa,dis);
	sort(P+1,P+tot+1,cmp);
	int Num=tot;tot=0;
	for(int i=1;i<=Num;i++){
		int j=i;
		while(j<Num&&P[j+1].dis==P[i].dis)P[i].num+=P[++j].num;
		P[++tot]=P[i];
		i=j;
	}
	for(int i=1;i<=m;i++)num+=f*Solve(p[i]);
}
void Divide(int x,int fa,int Size){
	Root=0;Min=inf;Find(x,0,Size);
	x=Root;Calc(x,0,0,1);vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		Calc(y,x,1,-1);
		Divide(y,x,sum[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++)p[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	Divide(1,0,n);
	double dlt=1.0*num/Sum(n);
	int a=n/3+(n%3>=1),b=n/3+(n%3>=2),c=n/3;
	printf("%.2lf\n%.2lf\n%.2lf",Sum(a)*dlt,Sum(b)*dlt,Sum(c)*dlt);
	return 0;
}