/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#include<set>
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
int n,m;
int A[N],B[N],fa[N],vis[N];
struct Node{int x,y,c;}P[N];
bool operator<(Node A,Node B){return A.c>B.c;}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
multiset<Node>F;
multiset<Node>::iterator it;
int Solve(){
	for(int i=1;i<=n*2;i++)fa[i]=i;
	for(it=F.begin();it!=F.end();it++){
		int x=(*it).x,y=(*it).y;
		fa[Find(A[x])]=Find(B[y]);
		fa[Find(A[y])]=Find(B[x]);
		if(Find(A[x])==Find(B[x]))return (*it).c;
		if(Find(A[y])==Find(B[y]))return (*it).c;
	}
	return 0;
}
int main(){
//	freopen("redgreen.in","r",stdin);
//	freopen("redgreen.out","w",stdout);
	n=read();m=read();
	int T=read();
	for(int i=1;i<=n;i++)A[i]=i;
	for(int i=1;i<=n;i++)B[i]=i+n;
	for(int i=1;i<=m;i++){
		P[i].x=read();
		P[i].y=read();
		P[i].c=read();
		F.insert(P[i]);
	}
	char op[5];
	while(T--){
		scanf("%s",op);
		if(op[0]=='D'){
			int id=read();
			if(vis[id])continue;
			it=F.find(P[id]);
			F.erase(it);
			vis[id]=1;
		}
		if(op[0]=='A'){
			m++;
			P[m].x=read();
			P[m].y=read();
			P[m].c=read();
			F.insert(P[m]);
		}
		if(op[0]=='Q'){
			printf("%d\n",Solve());
		}
	}
	return 0;
}