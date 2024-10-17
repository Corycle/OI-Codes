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
#define fst first
#define scd second
#define mp make_pair
#define pii pair<int,int>
#define y1 y_1
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
pii lst[N];
int n,m,Ans;
int a[2][N],fa[N],sum[N],Sum[N];
int id(int t,int x){return x+t*n;}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Union(int x,int y){x=Find(x);y=Find(y);if(x!=y){fa[x]=y;sum[y]+=sum[x];}}
void Update(pii A,pii B){
	int x1=id(A.fst,A.scd),x2=id(A.fst^1,A.scd);
	int y1=id(B.fst,B.scd),y2=id(B.fst^1,B.scd);
	Union(x1,y2);Union(x2,y1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n*2;i++){fa[i]=i;sum[i]=1;}
	for(int t=0;t<2;t++){
		for(int i=1;i<=n;i++){
			a[t][i]=read();
			if(lst[a[t][i]].scd){Update(lst[a[t][i]],mp(t,i));}
			lst[a[t][i]]=mp(t,i);
		}
	}
	for(int i=1;i<=n;i++)Sum[Find(id(0,i))]++;
	for(int i=1;i<=n;i++)if(Find(i)==i)Ans+=min(Sum[i],sum[i]-Sum[i]);
	printf("%d\n",Ans);
	return 0;
}
