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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,fa[N],sum[N],Ans[N];
struct Ques{int x,k,id;}q[N];
struct Edge{int x,y,d,id;}e[N];
bool cmp1(Edge A,Edge B){return A.d>B.d;}
bool cmp2(Ques A,Ques B){return A.k>B.k;}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Union(int x,int y){
	x=Find(x);y=Find(y);
	fa[x]=y;sum[y]+=sum[x];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		e[i]=(Edge){x,y,z,i};
	}
	for(int i=1;i<=m;i++){
		int k=read(),x=read();
		q[i]=(Ques){x,k,i};
	}
	int pos=1,i=1;
	sort(e+1,e+n,cmp1);
	sort(q+1,q+m+1,cmp2);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)sum[i]=1;
	for(int i=1;i<=m;i++){
		while(pos<n&&e[pos].d>=q[i].k){
			Union(e[pos].x,e[pos].y);pos++;
		}
		Ans[q[i].id]=sum[Find(q[i].x)]-1;
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}