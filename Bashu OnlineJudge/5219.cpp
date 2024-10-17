#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=500005;
const int M=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,top;
int a[M][M];
int fa[N],sum[N];
vector<int>v[N*4];
struct node{
	int x,y;
}st[N];
struct Ques{
	int type,l,r,s,t;
}q[N];
int Find(int x){
	return x==fa[x]?x:Find(fa[x]);
}
void Merge(int x,int y){
	x=Find(x);y=Find(y);
	if(x==y)return;
	if(sum[x]>sum[y])swap(x,y);
	st[++top]=(node){x,y};
	sum[y]+=sum[x];
	fa[x]=y;
}
void Delete(int k){
	while(top>k){
		int x=st[top].x;
		int y=st[top].y;
		sum[y]-=sum[x];
		top--;fa[x]=x;
	}
}
void Add(int x,int y,int z,int p,int l,int r){
	if(y<l||x>r)return;
	if(x<=l&&r<=y){
		v[p].push_back(z);
		return;
	}
	ll mid=(l+r)>>1;
	Add(x,y,z,lson);
	Add(x,y,z,rson);
}
void Solve(int p,int l,int r){
	int num=v[p].size(),tp=top;
	for(int i=0;i<num;i++){
		int s=q[v[p][i]].s;
		int t=q[v[p][i]].t;
		Merge(s,t);
	}
	if(l==r){
		if(q[l].type){
			if(Find(q[l].s)==Find(q[l].t))printf("Y\n");
			else printf("N\n");
		}
		return;
	}
	int mid=(l+r)>>1;
	Solve(lson);
	Solve(rson);
	Delete(tp);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int op=read(),x=read(),y=read();
		if(x>y)swap(x,y);
		if(op==0){
			q[i].l=a[x][y]=i;
			q[i].s=x;q[i].t=y;
		}
		if(op==1){
			q[a[x][y]].r=i;
		}
		if(op==2){
			q[i].type=1;
			q[i].s=x;q[i].t=y;
		}
	}
	for(int i=1;i<=n;i++){
		fa[i]=i;sum[i]=1;
	}
	for(int i=1;i<=m;i++){
		if(q[i].l&&!q[i].r)q[i].r=m+1;
		if(q[i].l){
			Add(q[i].l,q[i].r-1,i,1,1,m);
		}
	}
	Solve(1,1,m);
	return 0;
}