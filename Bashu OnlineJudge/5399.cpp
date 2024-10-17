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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,T,ans[N];
struct node{int x,y;};
vector<node>v[N*4];
struct Union_Find_set{
	int top;
	int fa[N],dis[N],sum[N];
	struct Stack{int x,y;}st[N];
	int Find(int x){
		return x==fa[x]?x:Find(fa[x]);
	}
	int Dist(int x){
		return x==fa[x]?dis[x]:Dist(fa[x])+dis[x];
	}
	int Prepare(){
		for(int i=1;i<=n;i++){
			fa[i]=i;
			sum[i]=1;
			dis[i]=0;
		}
	}
	void Union(int x,int y,int d){
		x=Find(x);y=Find(y);
		if(x==y)return;
		if(sum[x]<sum[y])swap(x,y);
		st[++top]=(Stack){x,y};
		sum[x]+=sum[y];
		dis[y]=d;
		fa[y]=x;
	}
	void Undo(int k){
		while(top>k){
			int x=st[top].x;
			int y=st[top].y;
			sum[x]-=sum[y];
			dis[y]=0;top--;
			fa[y]=y;
		}
	}
}F;
void Insert(int x,int y,int fx,int fy,int p,int l,int r){
	if(y<l||x>r)return;
	if(x<=l&&r<=y){
		v[p].push_back((node){fx,fy});
		return;
	}
	int mid=(l+r)>>1;
	Insert(x,y,fx,fy,lson);
	Insert(x,y,fx,fy,rson);
}
void Solve(int p,int l,int r){
	int tp=F.top;
	int num=v[p].size();
	for(int i=0;i<num;i++){
		int x=v[p][i].x,y=v[p][i].y;
		int fx=F.Find(x),fy=F.Find(y);
		int dx=F.Dist(x),dy=F.Dist(y);
		if(fx!=fy)F.Union(fx,fy,dx+dy+1);
		else{
			if((dx+dy+1)&1){
				F.Undo(tp);
				return;
			}
		}
	}
	if(l==r)ans[l]=1;
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
	n=read();m=read();T=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		int l=read(),r=read();
		if(l==r)continue;
		Insert(l+1,r,x,y,1,1,T);
	}
	F.Prepare();
	Solve(1,1,T);
	for(int i=1;i<=T;i++){
		if(ans[i])printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}