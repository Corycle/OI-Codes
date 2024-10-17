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
const int N=1e5+5;
const int M=350;
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
ll Ans[N*5],Sum;
vector<int>G[N];
int n,m,t1,t2,num,tot,qnt,Root;
struct Node{int l,r;}L1[5],L2[5];
struct Query{int p1,p2,f,id;}P[N*80];
int a[N],b[N],L[N],R[N],fa[N],st[N],ed[N],Pos[N],dep[N],pos[N],cnt1[N],cnt2[N],p[N][20];
bool cmp(Query A,Query B){return pos[A.p1]!=pos[B.p1]?pos[A.p1]<pos[B.p1]:A.p2<B.p2;}
void Prepare(){
	while(ed[num]!=n){num++;st[num]=ed[num-1]+1;ed[num]=min(ed[num-1]+M,n);}
	for(int i=1;i<=num;i++)for(int j=st[i];j<=ed[i];j++)pos[j]=i;
}
void DFS(int x,int depth){
	L[x]=++tot;Pos[tot]=x;dep[x]=depth;p[x][0]=fa[x];
	for(int i=1;i<20;i++)p[x][i]=p[p[x][i-1]][i-1];
	for(auto y:G[x])if(y!=fa[x]){fa[y]=x;DFS(y,depth+1);}
	R[x]=tot;
}
int Pre(int x,int y){for(int i=19;i>=0;i--)if(dep[y]-(1<<i)>dep[x])y=p[y][i];return y;}
void GetLine(int x,Node Line[],int &tot){
	tot=0;
	if(x==Root)Line[++tot]=(Node){1,n};
	else if(!(L[x]<=L[Root]&&L[Root]<=R[x]))Line[++tot]=(Node){L[x],R[x]};
	else{
		int fx=Pre(x,Root);
		if(L[fx]!=1)Line[++tot]=(Node){1,L[fx]-1};
		if(R[fx]!=n)Line[++tot]=(Node){R[fx]+1,n};
	}
}
void UpdateL(int x,int addv){cnt1[a[Pos[x]]]+=addv;Sum+=addv*cnt2[a[Pos[x]]];}
void UpdateR(int x,int addv){cnt2[a[Pos[x]]]+=addv;Sum+=addv*cnt1[a[Pos[x]]];}
void Insert(int l1,int r1,int l2,int r2,int id){
	P[++tot]=(Query){r1,r2,1,id};
	P[++tot]=(Query){l1-1,r2,-1,id};
	P[++tot]=(Query){r1,l2-1,-1,id};
	P[++tot]=(Query){l1-1,l2-1,1,id};
}
int main(){
//	freopen("_.in","p2",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+n+1);b[0]=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+b[0]+1,a[i])-b;
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	DFS(1,1);tot=0;Root=1;
	for(int i=1;i<=m;i++){
		int op=read();
		if(op==1)Root=read();
		if(op==2){
			int x=read(),y=read();qnt++;
			GetLine(x,L1,t1);
			GetLine(y,L2,t2);
			for(int p1=1;p1<=t1;p1++){
				for(int p2=1;p2<=t2;p2++){
					Insert(L1[p1].l,L1[p1].r,L2[p2].l,L2[p2].r,qnt);
				}
			}
		}
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
	for(int i=1;i<=qnt;i++)printf("%lld\n",Ans[i]);
	return 0;
}
