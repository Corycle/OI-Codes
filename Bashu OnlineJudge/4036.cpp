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
const int N=400005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,ans[N];
struct Ques{
	int l,r,x,y,type;
}q[N];
vector<int>v[N];
struct Union_Find_set{
	int top;
	int fa[N],sum[N];
	struct Stack{int x,y;}st[N];
	int Find(int x){
		return x==fa[x]?x:Find(fa[x]);
	}
	void Prepare(){
		for(int i=1;i<=n;i++){
			fa[i]=i;
			sum[i]=1;
		}
	}
	void Union(int x,int y){
		x=Find(x);y=Find(y);
		if(x==y)return;
		if(sum[x]<sum[y])swap(x,y);
		st[++top]=(Stack){x,y};
		sum[x]+=sum[y];
		fa[y]=x;
	}
	void Undo(int k){
		while(top>k){
			int x=st[top].x;
			int y=st[top].y;
			sum[x]-=sum[y];
			fa[y]=y;top--;
		}
	}
}F;
void Insert(int x,int y,int z,int p,int l,int r){
	if(y<l||x>r)return;
	if(x<=l&&r<=y){
		v[p].push_back(z);
		return;
	}
	int mid=(l+r)>>1;
	Insert(x,y,z,lson);
	Insert(x,y,z,rson);
}
void Solve(int p,int l,int r){
	int num=v[p].size(),tp=F.top;
	for(int i=0;i<num;i++){
		int x=q[v[p][i]].x;
		int y=q[v[p][i]].y;
		F.Union(x,y);
	}
	if(l==r){
		int x=F.Find(n);
		ans[l]=(F.sum[x]==n);
	}
	else{
		int mid=(l+r)>>1;
		Solve(lson);
		Solve(rson);
	}
	F.Undo(tp);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	F.Prepare();
	for(int i=1;i<=m;i++){
		q[i].l=1;
		q[i].x=read();
		q[i].y=read();
	}
	int p=read();
	for(int i=1;i<=p;i++){
		int num=read();
		for(int j=1;j<=num;j++){
			int x=read();
			if(q[x].l<=i-1){
				Insert(q[x].l,i-1,x,1,1,p);
			}
			q[x].l=i+1;
		}
	}
	for(int i=1;i<=m;i++){
		if(q[i].l<=p){
			Insert(q[i].l,p,i,1,1,p);
		}
	}
	Solve(1,1,p);
	for(int i=1;i<=p;i++){
		if(ans[i])printf("Connected\n");
		else printf("Disconnected\n");
	}
	return 0;
}