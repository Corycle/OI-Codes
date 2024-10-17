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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],t[N],t1[N],t2[N],Ans[N];
struct Node{int l,r,num;}P[N];
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<N;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
	int Query(int l,int r){return Ask(r)-Ask(l-1);}
}tree;
void Divide(int ql,int qr,int l,int r){
	if(l==r){
		for(int i=ql;i<=qr;i++){
			int val=(P[t[i]].l<=a[l]&&a[l]<=P[t[i]].r);
			if(val>=P[t[i]].num)Ans[l]++;
		}
		return;
	}
	int mid=(l+r)>>1,p1=0,p2=0,pos=ql;
	for(int i=l;i<=mid;i++)tree.Add(a[i],1);
	for(int i=ql;i<=qr;i++){
		int tmp=tree.Query(P[t[i]].l,P[t[i]].r);
		if(P[t[i]].num<=tmp)t1[++p1]=t[i];
		else{P[t[i]].num-=tmp;t2[++p2]=t[i];}
	}
	for(int i=l;i<=mid;i++)tree.Add(a[i],-1);
	for(int i=1;i<=p1;i++)t[pos++]=t1[i];
	for(int i=1;i<=p2;i++)t[pos++]=t2[i];
	Divide(ql,ql+p1-1,l,mid);
	Divide(ql+p1,qr,mid+1,r);
}
int main(){
//	freopen("shooting.in","r",stdin);
//	freopen("shooting.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		t[i]=i;
		P[i].l=read();
		P[i].r=read();
		P[i].num=read();
	}
	for(int i=1;i<=m;i++)a[i]=read();
	Divide(1,n,1,m);
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}