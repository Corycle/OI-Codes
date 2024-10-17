/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,len1,len2;
int Rchain[N],Lchain[N];
int Lbr[N],Rbr[N],h1[N],h2[N];
int w[N],f[N],L[N],R[N],fa[N],Max[N];
vector<int>G[N];
inline void Solve(int x,int y){
	int p=x,q=y,id=0,d=w[fa[x]];
	Rchain[0]=fa[x];Rchain[len1=1]=x;
	Lchain[0]=fa[y];Lchain[len2=1]=y;
	while(R[p])Rchain[++len1]=(p=R[p]);
	while(L[q])Lchain[++len2]=(q=L[q]);
	Rchain[len1+1]=0;Lchain[len2+1]=0;
	Max[1]=d;Max[len1+1]=inf;
	h1[0]=-inf;h1[len1+1]=inf;
	h2[0]=inf;h2[len1+1]=-inf;
	for(register int i=2;i<=len1;i++)Max[i]=max(Max[i-1],w[Rchain[i-1]]);
	for(register int i=1;i<=len1;i++)h1[i]=max(h1[i-1],f[Rchain[i]]);
	for(register int i=len1;i>=1;i--)h2[i]=max(h2[i+1],f[Rchain[i]]-Max[i]);
	for(register int i=1;i<=len2;i++){
		while(id<len1&&Max[id+1]<=d)id++;
		f[Lchain[i]]=max(h1[id]-d,h2[id+1])+w[Lchain[i]];
		d=max(d,w[Lchain[i]]);
	}
}
inline void DFS(int x){
	int num=G[x].size();
	for(int i=0;i<num;i++){
		int y=G[x][i];DFS(y);
	}
	if(Rbr[x])Solve(x,Rbr[x]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(register int i=1;i<=n;i++){
		w[i]=read();
		int k=read();
		for(register int j=0;j<k;j++){
			int x=read();fa[x]=i;
			G[i].push_back(x);
			if(j){
				Lbr[G[i][j]]=G[i][j-1];
				Rbr[G[i][j-1]]=G[i][j];
			}
		}
		if(k){L[i]=G[i][0];R[i]=G[i][k-1];}
	}
	int p=1;f[p]=w[p];
	while(L[p]){p=L[p];f[p]=w[p];}
	DFS(1);int q=1,Ans=w[1];
	while(R[q]){q=R[q];Ans=max(Ans,f[q]);}
	printf("%d",Ans);
	return 0;
}