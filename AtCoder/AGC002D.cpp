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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,q,Ans[N];
struct Edge{int x,y;}E[N];
struct Ques{int x,y,k,id;}Q[N],t1[N],t2[N];
struct Union_Set{
	int top,st[N],fa[N],sum[N];
	int Find(int x){return x==fa[x]?x:Find(fa[x]);}
	void Init(){for(int i=1;i<=n;i++){fa[i]=i;sum[i]=1;}}
	void Union(int x,int y){
		x=Find(x);y=Find(y);if(x==y)return;
		if(sum[x]>sum[y])swap(x,y);fa[x]=y;sum[y]+=sum[x];st[++top]=x;
	}
	void Reset(int tmp){while(top>tmp){int x=st[top--];sum[fa[x]]-=sum[x];fa[x]=x;}}
	int Calc(int x,int y){x=Find(x);y=Find(y);return x==y?sum[x]:sum[x]+sum[y];}
}F;
void Divide(int ql,int qr,int l,int r){
	if(l==r){for(int i=ql;i<=qr;i++)Ans[Q[i].id]=l;return;}
	int mid=(l+r)>>1,tmp=F.top,p1=0,p2=0;
	for(int i=l;i<=mid;i++)F.Union(E[i].x,E[i].y);
	for(int i=ql;i<=qr;i++){
		if(F.Calc(Q[i].x,Q[i].y)>=Q[i].k)t1[++p1]=Q[i];
		else t2[++p2]=Q[i];
	}
	int pos=ql-1;
	for(int i=1;i<=p1;i++)Q[++pos]=t1[i];
	for(int i=1;i<=p2;i++)Q[++pos]=t2[i];
	F.Reset(tmp);
	if(p1)Divide(ql,ql+p1-1,l,mid);
	for(int i=l;i<=mid;i++)F.Union(E[i].x,E[i].y);
	if(p2)Divide(ql+p1,qr,mid+1,r);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	m=read();for(int i=1;i<=m;i++){E[i].x=read();E[i].y=read();}
	q=read();for(int i=1;i<=q;i++){Q[i].x=read();Q[i].y=read();Q[i].k=read();Q[i].id=i;}
	F.Init();Divide(1,q,1,m);
	for(int i=1;i<=q;i++)printf("%d\n",Ans[i]);
	return 0;
}
