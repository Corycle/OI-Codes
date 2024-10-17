/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<bitset>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define Bitset bitset<N>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=155;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,lst,Ans,a[N],dis[N];
struct Edge{int x,y,d;}E[N];
bool cmp(Edge A,Edge B){return A.d<B.d;}
struct Matrix{
	Bitset a[N];
	void Clear(){for(int i=1;i<=n;i++)a[i].reset();}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Clear();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(A.a[i][j])C.a[i]|=B.a[j];
			}
		}
		return C;
	}
	friend Bitset operator*(Bitset A,Matrix B){
		Bitset C;C.reset();
		for(int i=1;i<=n;i++){
			C[i]=(A&B.a[i]).any();
		}
		return C;
	}
}A;
Bitset vis;
void Pow(Matrix A,int t,Bitset &ans){//return ans*Pow(A,t)
	while(t){
		if(t&1)ans=ans*A;
		A=A*A;t>>=1;
	}
}
bool BFS(){
	queue<int>q;
	for(int i=1;i<=n;i++)dis[i]=-1;
	for(int i=1;i<=n;i++)if(vis[i]){q.push(i);dis[i]=0;}
	while(q.size()){
		int x=q.front();q.pop();
		for(int y=1;y<=n;y++){
			if(A.a[y][x]&&dis[y]==-1){
				dis[y]=dis[x]+1;q.push(y);
			}
		}
	}
	return dis[n]!=-1;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Ans=inf;
	for(int i=1;i<=m;i++){
		E[i].x=read();
		E[i].y=read();
		E[i].d=read();
	}
	vis[1]=1;
	sort(E+1,E+m+1,cmp);
	for(int i=1;i<=m;i++){
		if(E[i].d>=Ans)break;
		Pow(A,E[i].d-lst,vis);
		A.a[E[i].y][E[i].x]=1;lst=E[i].d;
		if(BFS())Ans=min(Ans,lst+dis[n]);
	}
	if(Ans==inf)puts("Impossible");
	else printf("%d",Ans);
	return 0;
}
