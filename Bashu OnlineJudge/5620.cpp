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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,A,Min;
int a[N],pos[N];
priority_queue<int>q;
struct Node{int l,r;}P[N];
bool cmp(Node A,Node B){return A.l!=B.l?A.l<B.l:A.r<B.r;}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Init(){for(int i=1;i<=n;i++)c[i]=0;}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree;
bool Check(int Lim){
	tree.Init();
	int p=0,tot=0,cnt=0;
	while(q.size())q.pop();
	for(int i=1;i<=n;i++)if(a[i]<Lim)pos[++tot]=i;
	for(int i=1;i<=tot;i++){
		while(p<m&&P[p+1].l<=pos[i]){
			q.push(upper_bound(pos+1,pos+tot+1,P[++p].r)-pos-1);
		}
		while(a[pos[i]]+tree.Ask(i)<Lim){
			cnt++;
			if(cnt>K||!q.size())return false;
			tree.Add(i,A);
			tree.Add(q.top()+1,-A);
			q.pop();
		}
	}
	return true;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();m=read();K=read();A=read();Min=inf;
		for(int i=1;i<=n;i++)Min=min(Min,a[i]=read());
		for(int i=1;i<=m;i++){P[i].l=read();P[i].r=read();}
		sort(P+1,P+m+1,cmp);
		int l=Min,r=Min+K*A,Ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(Check(mid)){
				Ans=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		printf("%d\n",Ans);
	}
	return 0;
}