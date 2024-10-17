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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
map<int,int>lst;
int a[N],sum[N],Ans[N];
struct Ques{int l,r,id,type;}Q[N];
bool cmp(Ques A,Ques B){return A.r<B.r;}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]^=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans^=c[x];return ans;}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	read();n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum[i]=sum[i-1]^a[i];
	}
	for(int i=1;i<=m;i++){
		Q[i].id=i;
		Q[i].l=read();
		Q[i].r=read();
		Q[i].type=read();
	}
	int pos=0;
	sort(Q+1,Q+m+1,cmp);
	for(int i=1;i<=m;i++){
		while(pos<Q[i].r){
			pos++;
			if(lst[a[pos]]){
				tree.Add(1,a[pos]);
				tree.Add(lst[a[pos]]+1,a[pos]);
			}
			lst[a[pos]]=pos;
		}
		if(Q[i].type==0)Ans[Q[i].id]=sum[Q[i].r]^sum[Q[i].l-1];
		if(Q[i].type==1)Ans[Q[i].id]=tree.Ask(Q[i].l);
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}