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
const int M=1e6+5;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,f[N],Ans[M];
struct Node{int a,b,c;}P[N];
struct Ques{int m,k,s,id;}Q[M];
bool cmp1(Node A,Node B){return A.a<B.a;}
bool cmp2(Ques A,Ques B){return A.m<B.m;}
void Update(int id){for(int k=N-P[id].c-1;k>=0;k--)f[k+P[id].c]=max(f[k+P[id].c],min(f[k],P[id].b));}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();for(int i=1;i<=n;i++){P[i].c=read();P[i].a=read();P[i].b=read();}
	m=read();for(int i=1;i<=m;i++){Q[i].m=read();Q[i].k=read();Q[i].s=read();Q[i].id=i;}
	sort(P+1,P+n+1,cmp1);sort(Q+1,Q+m+1,cmp2);f[0]=inf;
	for(int i=1,j=1;i<=m;i++){
		while(j<=n&&P[j].a<=Q[i].m)Update(j++);
		Ans[Q[i].id]=(f[Q[i].k]>Q[i].m+Q[i].s);
	}
	for(int i=1;i<=m;i++)puts(Ans[i]?"TAK":"NIE");
	return 0;
}
