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
#include<unordered_map>
#define fst first
#define scd second
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
const int M=31;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans[M];
unordered_map<int,int>lst;
struct Line_Basis{
	int num,p[M];
	void Insert(int x){
		for(int i=m-1;i>=0;i--){
			if((x>>i)&1){
				if(p[i])x^=p[i];
				else{p[i]=x;num++;break;}
			}
		}
	}
}F;
struct Segment_Tree{
	vector<int>G[N*4];
	void Update(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){G[p].push_back(z);return;}
		int mid=(l+r)>>1;
		Update(x,y,z,lson);Update(x,y,z,rson);
	}
	void Query(Line_Basis F,int p,int l,int r){
		for(auto x:G[p])F.Insert(x);
		if(l==r){printf("%d\n",Ans[F.num]);return;}
		int mid=(l+r)>>1;
		Query(F,lson);Query(F,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();n=read();
	for(int i=1;i<=n;i++){
		int op=read(),x=read();
		if(op==1)lst[x]=i;
		if(op==2){tree.Update(lst[x],i-1,x,1,1,n);lst[x]=0;}
	}
	Ans[0]=1;
	for(int i=1;i<=m;i++)Ans[i]=Ans[i-1]*2;
	for(auto t:lst)if(t.scd)tree.Update(t.scd,n,t.fst,1,1,n);
	tree.Query(F,1,1,n);
	return 0;
}