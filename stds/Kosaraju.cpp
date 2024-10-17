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
	if(A.l/blk==B.l/blk)return((A.l/blk&1)?A.r<B.r:A.r>B.r);
	return A.l/blk<B.l/blk;
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
	
	return 0;
}
