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
const ll inf=9e18;
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,fa[N];
struct Vector{
	ll x,y;
	friend ll operator*(Vector A,Vector B){return A.x*B.y-A.y*B.x;}
	friend Vector operator-(Vector A,Vector B){return (Vector){A.x-B.x,A.y-B.y};}
}S,T;
struct edge{int x,y,a,b;ll w;}e[N];
bool cmp(edge A,edge B){return A.w<B.w;}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
Vector Kruskal(){
	ll sum1=0,sum2=0;
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=Find(e[i].x),y=Find(e[i].y);
		if(x==y)continue;
		fa[x]=y;sum1+=e[i].a;sum2+=e[i].b;
	}
	return (Vector){sum1,sum2};
}
void Solve(Vector A,Vector B){
	Ans=min(Ans,min(A.x*A.y,B.x*B.y));
	for(int i=1;i<=m;i++){
		e[i].w=(Vector){e[i].a,e[i].b}*(A-B);
	}
	Vector C=Kruskal();
	if((C-A)*(C-B)>=0)return;
	Solve(A,C);Solve(C,B);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Ans=inf;
	for(int i=1;i<=m;i++){
		e[i].x=read();e[i].y=read();
		e[i].a=read();e[i].b=read();
	}
	for(int i=1;i<=m;i++)e[i].w=e[i].a;S=Kruskal();
	for(int i=1;i<=m;i++)e[i].w=e[i].b;T=Kruskal();
	Solve(S,T);
	printf("%lld",Ans);
	return 0;
}