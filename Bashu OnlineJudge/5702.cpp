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
const int Mod=1e9+7;
const int N=100005;
const int M=100;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,a[N],b[N],Root[N];
int mod(int x){return x>=Mod?x-Mod:x;}
struct Answer{
	int sum,num;
	friend Answer operator+(Answer A,Answer B){
		return (Answer){(A.sum+B.sum)%Mod,A.num+B.num};
	}
	friend Answer operator-(Answer A,Answer B){
		return (Answer){(A.sum-B.sum)%Mod,A.num-B.num};
	}
};
struct Node{int l,r;Answer ans;};
struct Segment_Tree{
	int tot;
	Node t[N*M];
	void Update(int pos,Answer val,int &p,int l,int r){
		if(!p)p=++tot;t[p].ans=t[p].ans+val;
		if(l==r)return;int mid=(l+r)>>1;
		if(pos<=mid)Update(pos,val,t[p].l,l,mid);
		if(pos>mid)Update(pos,val,t[p].r,mid+1,r);
	}
	Answer Query(int x,int y,int p,int l,int r){
		if(y<l||x>r||!p)return (Answer){0,0};
		if(x<=l&&r<=y)return t[p].ans;
		int mid=(l+r)>>1;
		return Query(x,y,t[p].l,l,mid)+Query(x,y,t[p].r,mid+1,r);
	}
}Tree;
struct BIT{
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y,Answer val){
		for(;x<=n;x+=lowbit(x))Tree.Update(y,val,Root[x],1,n);
	}
	Answer Ask(int x,int l,int r){
		Answer ans=(Answer){0,0};
		for(;x>=1;x-=lowbit(x))ans=ans+Tree.Query(l,r,Root[x],1,n);
		return ans;
	}
	Answer Query(int x,int y,int l,int r){
		return Ask(y,l,r)-Ask(x-1,l,r);
	}
}tree;
void Update(int x,int y,int l,int r,int val,int f){
	if(l>r)return;
	Answer tmp=tree.Query(x,y,l,r);
	Ans=(Ans+1ll*f*tmp.sum%Mod)%Mod;
	Ans=(Ans+1ll*f*tmp.num*val%Mod)%Mod;
	Ans=(Ans%Mod+Mod)%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();b[i]=read();
		Answer tmp=tree.Ask(i-1,a[i]+1,n);
		tree.Add(i,a[i],(Answer){b[i],1});
		Ans=mod(mod(Ans+tmp.sum)+1ll*tmp.num*b[i]%Mod);
	}
	while(m--){
		int x=read(),y=read();
		if(x==y){printf("%d\n",Ans);continue;}
		if(x>y)swap(x,y);
		if(y-x>=2){
			Update(x+1,y-1,1,a[x]-1,b[x],-1);
			Update(x+1,y-1,a[y]+1,n,b[y],-1);
			Update(x+1,y-1,a[x]+1,n,b[x],1);
			Update(x+1,y-1,1,a[y]-1,b[y],1);
		}
		if(a[x]<a[y])Ans+=b[x]+b[y];
		if(a[x]>a[y])Ans-=b[x]+b[y];
		Ans=(Ans%Mod+Mod)%Mod;
		printf("%d\n",Ans);
		
		tree.Add(x,a[x],(Answer){-b[x],-1});
		tree.Add(y,a[y],(Answer){-b[y],-1});
		swap(a[x],a[y]);swap(b[x],b[y]);
		tree.Add(x,a[x],(Answer){b[x],1});
		tree.Add(y,a[y],(Answer){b[y],1});
	}
	return 0;
}