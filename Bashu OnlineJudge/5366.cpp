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
const int Base=1e8;
const int M=10005;
const int N=2022;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int fa[M],a[N][N],b[N][N];
struct Number{
	ll a[N];
	void Init(int x){
		a[0]=1;a[1]=x;
	}
	friend Number operator+(Number A,int B){
		A.a[1]+=B;
		for(int i=1;i<=A.a[0];i++){
			if(A.a[i]>=Base){
				if(i==A.a[0])A.a[++A.a[0]]=0;
				A.a[i+1]+=A.a[i]/Base;
				A.a[i]%=Base;
			}
		}
		return A;
	}
	friend Number operator*(Number A,Number B){
		Number C;C.Init(0);
		C.a[0]=A.a[0]+B.a[0];
		for(int i=1;i<=C.a[0];i++)C.a[i]=0;
		for(int i=1;i<=A.a[0];i++){
			for(int j=1;j<=B.a[0];j++){
				C.a[i+j-1]+=A.a[i]*B.a[j];
			}
		}
		for(int i=1;i<=C.a[0];i++){
			if(C.a[i]>=Base){
				C.a[i+1]+=C.a[i]/Base;
				C.a[i]%=Base;
			}
		}
		while(C.a[0]>1&&!C.a[C.a[0]])C.a[0]--;
		return C;
	}
};
Number Ans[M];
struct Node{int x,y,h;}P[M];
bool cmp(Node A,Node B){return A.h<B.h;}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Print(Number A){
	printf("%lld",A.a[A.a[0]]);
	for(int i=A.a[0]-1;i>=1;i--)printf("%08lld",A.a[i]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			tot++;
			P[tot].h=read();
			P[tot].x=i;P[tot].y=j;
		}
	}
	sort(P+1,P+tot+1,cmp);
	for(int i=1;i<=tot;i++){
		fa[i]=i;
		Ans[i].Init(1);
		b[P[i].x][P[i].y]=i;
	}
	for(int i=1;i<=tot;i++){
		int x=P[i].x,y=P[i].y;
		for(int j=0;j<4;j++){
			int fx=x+dx[j],fy=y+dy[j];
			if(fx<1||fx>n||fy<1||fy>n)continue;
			int A=Find(b[x][y]),B=Find(b[fx][fy]);
			if(A!=B&&P[A].h>=P[B].h){
				fa[B]=A;
				Ans[A]=Ans[A]*(Ans[B]+(P[A].h-P[B].h));
			}
		}
	}
	int t=Find(1);
	Print(Ans[t]+(m-P[t].h));
	return 0;
}