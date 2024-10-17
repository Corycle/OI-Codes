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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,b[N],Ans[N];
struct Node{int x,y,z,t;}P[N],tmp[N];
bool cmp(Node A,Node B){return A.x!=B.x?A.x<B.x:A.t<B.t;}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<N;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree;
void CDQ(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	CDQ(l,mid);CDQ(mid+1,r);
	int p1=l,p2=mid+1,pos=l;
	while(p1<=mid&&p2<=r){
		if(P[p1].y<=P[p2].y){if(P[p1].t==0)tree.Add(P[p1].z,1);tmp[pos++]=P[p1++];}
		else{if(P[p2].t!=0)Ans[P[p2].t]+=tree.Ask(P[p2].z);tmp[pos++]=P[p2++];}
	}
	while(p1<=mid){if(P[p1].t==0)tree.Add(P[p1].z,1);tmp[pos++]=P[p1++];}
	while(p2<=r){if(P[p2].t!=0)Ans[P[p2].t]+=tree.Ask(P[p2].z);tmp[pos++]=P[p2++];}
	for(int i=l;i<=mid;i++)if(P[i].t==0)tree.Add(P[i].z,-1);
	for(int i=l;i<=r;i++)P[i]=tmp[i];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){int x=read(),y=read();P[++tot]=(Node){x,y,x+y,0};}
	for(int i=1;i<=m;i++){int x=read(),y=read(),z=read();P[++tot]=(Node){x,y,z,i};}
	for(int i=1;i<=tot;i++){b[++b[0]]=-P[i].x;b[++b[0]]=-P[i].y;b[++b[0]]=-P[i].z;}
	sort(b+1,b+b[0]+1);b[0]=unique(b+1,b+b[0]+1)-b-1;
	for(int i=1;i<=tot;i++){
		P[i].x=lower_bound(b+1,b+b[0]+1,-P[i].x)-b;
		P[i].y=lower_bound(b+1,b+b[0]+1,-P[i].y)-b;
		P[i].z=lower_bound(b+1,b+b[0]+1,-P[i].z)-b;
	}
	sort(P+1,P+tot+1,cmp);
	CDQ(1,tot);
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}