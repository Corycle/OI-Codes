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
const int N=5e4+5;
const int M=200;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans[N],Sum;
int n,m,num,tot;
int a[N],st[N],ed[N],pos[N],cnt1[N],cnt2[N];
struct Query{int p1,p2,f,id;}P[N*4];
bool cmp(Query A,Query B){return pos[A.p1]!=pos[B.p1]?pos[A.p1]<pos[B.p1]:A.p2<B.p2;}
void Prepare(){
	while(ed[num]!=n){num++;st[num]=ed[num-1]+1;ed[num]=min(ed[num-1]+M,n);}
	for(int i=1;i<=num;i++)for(int j=st[i];j<=ed[i];j++)pos[j]=i;
}
void UpdateL(int x,int addv){cnt1[a[x]]+=addv;Sum+=addv*cnt2[a[x]];}
void UpdateR(int x,int addv){cnt2[a[x]]+=addv;Sum+=addv*cnt1[a[x]];}
int main(){
//	freopen("_.in","p2",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare();
	for(int i=1;i<=n;i++)a[i]=read();
	m=read();
	for(int i=1;i<=m;i++){
		int l1=read(),r1=read(),l2=read(),r2=read();
		P[++tot]=(Query){r1,r2,1,i};
		P[++tot]=(Query){l1-1,r2,-1,i};
		P[++tot]=(Query){r1,l2-1,-1,i};
		P[++tot]=(Query){l1-1,l2-1,1,i};
	}
	for(int i=1;i<=tot;i++)if(P[i].p1>P[i].p2)swap(P[i].p1,P[i].p2);
	sort(P+1,P+tot+1,cmp);
	int p1=0,p2=0;
	for(int i=1;i<=tot;i++){
		while(p1<P[i].p1)UpdateL(++p1,1);
		while(p2<P[i].p2)UpdateR(++p2,1);
		while(p1>P[i].p1)UpdateL(p1--,-1);
		while(p2>P[i].p2)UpdateR(p2--,-1);
		Ans[P[i].id]+=P[i].f*Sum;
	}
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}