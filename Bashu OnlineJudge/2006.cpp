/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
#include<unordered_map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
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
int n,m,K,Q,cnt;
int a[N],b[N],h[N],fa[N],val[N];
struct Edge{int x,y,val;}E[N];
struct edge{int to,next,dist;}d[N*2];
bool cmp(Edge A,Edge B){return A.val<B.val;}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
struct Node{
	int c,val;
	friend bool operator==(Node A,Node B){return A.c==B.c&&A.val==B.val;}
	friend bool operator<(Node A,Node B){return A.val!=B.val?A.val>B.val:A.c>B.c;}
};
struct Heap{
	priority_queue<Node>q1,q2;
	void Insert(Node A){if(A.c)q1.push(A);}
	void Delete(Node A){if(A.c)q2.push(A);}
	Node Top(){
		while(q2.size()&&q1.top()==q2.top()){q1.pop();q2.pop();}
		return q1.size()?q1.top():(Node){0,inf};
	}
}P[N],Answer;
unordered_map<int,Heap>F[N];
Node GetAns(int x){
	Node tmp=P[x].Top();
	if(tmp.c!=a[x])return tmp;
	else{P[x].Delete(tmp);Node ans=P[x].Top();P[x].Insert(tmp);return ans;}
}
void DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y);val[y]=d[i].dist;
		F[x][a[y]].Insert((Node){a[y],val[y]});
	}
	int tot=0;
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y!=fa[x])b[++tot]=a[y];}
	sort(b+1,b+tot+1);tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1;i<=tot;i++)P[x].Insert(F[x][b[i]].Top());
	Answer.Insert(GetAns(x));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();Q=read();
	for(int i=1;i<=m;i++){E[i].x=read();E[i].y=read();E[i].val=read();}
	for(int i=1;i<=n;i++){a[i]=read();fa[i]=i;}
	sort(E+1,E+m+1,cmp);
	for(int i=1;i<=m;i++){
		int x=Find(E[i].x),y=Find(E[i].y);
		if(x==y)continue;
		fa[Find(x)]=Find(y);
		Add(E[i].x,E[i].y,E[i].val);
		Add(E[i].y,E[i].x,E[i].val);
	}
	for(int i=1;i<=n;i++)fa[i]=0;
	DFS(1);
	while(Q--){
		int x=read();
		if(fa[x]){
			Answer.Delete(GetAns(fa[x]));
			P[fa[x]].Delete(F[fa[x]][a[x]].Top());
			F[fa[x]][a[x]].Delete((Node){a[x],val[x]});
			P[fa[x]].Insert(F[fa[x]][a[x]].Top());
		}
		Answer.Delete(GetAns(x));
		a[x]=read();
		Answer.Insert(GetAns(x));
		if(fa[x]){
			P[fa[x]].Delete(F[fa[x]][a[x]].Top());
			F[fa[x]][a[x]].Insert((Node){a[x],val[x]});
			P[fa[x]].Insert(F[fa[x]][a[x]].Top());
			Answer.Insert(GetAns(fa[x]));
		}
		printf("%d\n",Answer.Top().val);
	}
	return 0;
}
