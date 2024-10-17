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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,ta,tb,Ans1,Ans2,fa[N];
struct Vector{
	int x,y;
	friend int operator*(Vector A,Vector B){return A.x*B.y-A.y*B.x;}
	friend Vector operator-(Vector A,Vector B){return (Vector){A.x-B.x,A.y-B.y};}
}S,T;
struct edge{int x,y,a,b;}e[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline Vector Kruskal(int a,int b){
	int sum1=0,sum2=0;ta=a;tb=b;
	sort(e+1,e+m+1,[](edge A,edge B){return A.a*tb-A.b*ta<B.a*tb-B.b*ta;});
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=Find(e[i].x),y=Find(e[i].y);
		if(x==y)continue;
		fa[x]=y;sum1+=e[i].a;sum2+=e[i].b;
	}
	return (Vector){sum1,sum2};
}
inline void Solve(Vector A,Vector B){
	Vector C=Kruskal(A.x-B.x,A.y-B.y);
	if((A-C)*(B-C)>=0)return;
	if(Ans1*Ans2>C.x*C.y){Ans1=C.x;Ans2=C.y;}
	Solve(A,C);Solve(C,B);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	Ans1=inf;Ans2=1;
	for(int i=1;i<=m;i++){
		e[i].x=read()+1;
		e[i].y=read()+1;
		e[i].a=read();
		e[i].b=read();
	}
	S=Kruskal(0,1);T=Kruskal(-1,0);
	if(Ans1*Ans2>S.x*S.y){Ans1=S.x;Ans2=S.y;}
	if(Ans1*Ans2>T.x*T.y){Ans1=T.x;Ans2=T.y;}
	Solve(S,T);
	printf("%d %d",Ans1,Ans2);
	return 0;
}