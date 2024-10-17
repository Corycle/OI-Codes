#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int M=300005;
const int N=205;
inline int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Q,tot,top,blk,num;
struct Edge{int s,t;}e[M];
struct Ques{int l,r,id;}q[M];
int a[N][N],st[N],ed[N],Ans[M],pos[M],Stack[N];
struct Bitset{
	unsigned int b[8];
	void Set(int x){b[x>>5]|=1u<<(x&31);}
	void Rev(int x){b[x>>5]^=1u<<(x&31);}
	void Reset(){for(int i=0;i<8;i++)b[i]=0;}
	bool Date(int x){return b[x>>5]>>(x&31)&1;}
}G1[N],G2[N],vis;
bool cmp(Ques A,Ques B){
//	if(pos[A.l]==pos[B.l])return A.r<B.r;
//	return pos[A.l]<pos[B.l];
	if(A.l/blk==B.l/blk)return((A.l/blk&1)?A.r<B.r:A.r>B.r);
	return A.l/blk<B.l/blk;
}
void Prepare(){
	blk=2000;
//	num=m/blk;
//	for(int i=1;i<=num;i++){st[i]=ed[i-1]+1;ed[i]=ed[i-1]+blk;}
//	if(ed[num]!=m){num++;st[num]=ed[num-1]+1;ed[num]=m;}
//	for(int i=1;i<=num;i++){
//		for(int j=st[i];j<=ed[i];j++){
//			pos[j]=i;
//		}
//	}
}
inline void Update(int x,int addv){
	a[e[x].s][e[x].t]+=addv;
	if(addv==1&&a[e[x].s][e[x].t]==1){
		G1[e[x].s].Set(e[x].t);
		G2[e[x].t].Set(e[x].s);
	}
	else if(addv==-1&&a[e[x].s][e[x].t]==0){
		G1[e[x].s].Rev(e[x].t);
		G2[e[x].t].Rev(e[x].s);
	}
}
void DFS1(int x){
	vis.Rev(x);
	for(int i=0;i<8;i++){
		while(1){
			unsigned int tmp=vis.b[i]&G1[x].b[i];
			if(!tmp)break;
			DFS1(i<<5|__builtin_ctz(tmp));
		}
	}
	Stack[++top]=x;
}
void DFS2(int x){
	vis.Rev(x);tot++;
	for(int i=0;i<8;i++){
		while(1){
			unsigned int tmp=vis.b[i]&G2[x].b[i];
			if(!tmp)break;
			DFS2(i<<5|__builtin_ctz(tmp));
		}
	}
}
int Kosaraju(){
	vis.Reset();
	int ans=0;top=0;
	for(int i=1;i<=n;i++)vis.Set(i);
	for(int i=1;i<=n;i++)if(vis.Date(i))DFS1(i);
	for(int i=1;i<=n;i++)vis.Set(i);
	while(top){
		if(vis.Date(Stack[top])){
			tot=0;
			DFS2(Stack[top]);
			ans+=tot*(tot-1)/2;
		}
		top--;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=m;i++){e[i].s=read();e[i].t=read();}
	for(int i=1;i<=Q;i++){q[i].l=read();q[i].r=read();q[i].id=i;}
	Prepare();sort(q+1,q+Q+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=Q;i++){
		while(l>q[i].l)Update(--l,1);
		while(r<q[i].r)Update(++r,1);
		while(l<q[i].l)Update(l++,-1);
		while(r>q[i].r)Update(r--,-1);
		Ans[q[i].id]=Kosaraju();
	}
	for(int i=1;i<=Q;i++){
		printf("%d\n",Ans[i]);
	}
	return 0;
}