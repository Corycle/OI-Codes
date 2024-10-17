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
const int N=3e6+5;
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
int n,m,tot,b[N],Ans[N];
struct Node{int x,y,op,id;}P[N];
bool cmp(Node A,Node B){return A.x!=B.x?A.x<B.x:(A.y!=B.y?A.y<B.y:A.op<B.op);}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<N;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		b[++b[0]]=x;b[++b[0]]=y;
		P[++tot]=(Node){x,y,1,0};
	}
	for(int i=1;i<=m;i++){
		int sx=read(),sy=read(),tx=read(),ty=read();
		P[++tot]=(Node){tx,ty,2,i};
		P[++tot]=(Node){tx,sy-1,3,i};
		P[++tot]=(Node){sx-1,ty,3,i};
		P[++tot]=(Node){sx-1,sy-1,2,i};
		b[++b[0]]=tx;b[++b[0]]=sx-1;
		b[++b[0]]=ty;b[++b[0]]=sy-1;
	}
	sort(b+1,b+b[0]+1);b[0]=unique(b+1,b+b[0]+1)-b-1;
	for(int i=1;i<=tot;i++){
		P[i].x=lower_bound(b+1,b+b[0]+1,P[i].x)-b;
		P[i].y=lower_bound(b+1,b+b[0]+1,P[i].y)-b;
	}
	sort(P+1,P+tot+1,cmp);
	for(int i=1;i<=tot;i++){
		if(P[i].op==1)tree.Add(P[i].y,1);
		else if(P[i].op==2)Ans[P[i].id]+=tree.Ask(P[i].y);
		else if(P[i].op==3)Ans[P[i].id]-=tree.Ask(P[i].y);
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}