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
using namespace std;
const int inf=0x3f3f3f3f;
const int M=1000000000;
const int N=400005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot;
int rt[N],fa[N];
struct Tree{
	int l,r,data,bj;
	double sum;
}t[N*20];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Del(int x){
	t[x].bj=1;
	t[x].data=t[x].sum=0;
}
void Pushdown(int x){
	if(t[x].bj){
		if(t[x].l)Del(t[x].l);
		if(t[x].r)Del(t[x].r);
		t[x].bj=0;
	}
}
void Pushup(int x){
	t[x].sum=t[t[x].l].sum+t[t[x].r].sum;
	t[x].data=t[t[x].l].data+t[t[x].r].data;
}
void Insert(int &x,int y,int addv,int l,int r){
	if(!x)x=++tot;
	if(l==r){
		t[x].data+=addv;
		t[x].sum+=log(y)*addv;
		return;
	}
	Pushdown(x);
	int mid=(l+r)>>1;
	if(y<=mid)Insert(t[x].l,y,addv,l,mid);
	if(y>mid)Insert(t[x].r,y,addv,mid+1,r);
	Pushup(x);
}
int Merge(int x,int y){
	if(!x||!y)return x+y;
	t[x].sum+=t[y].sum;
	t[x].data+=t[y].data;
	Pushdown(x);Pushdown(y);
	t[x].l=Merge(t[x].l,t[y].l);
	t[x].r=Merge(t[x].r,t[y].r);
	return x;
}
int Sum(int x,int a,int b,int l,int r){
	if(b<l||a>r)return 0;
	if(a<=l&&r<=b)return t[x].data;
	Pushdown(x);
	int mid=(l+r)>>1,total=0;
	if(t[x].l)total+=Sum(t[x].l,a,b,l,mid);
	if(t[x].r)total+=Sum(t[x].r,a,b,mid+1,r);
	return total;
}
void Delete(int x,int a,int b,int l,int r){
	if(b<l||a>r)return;
	if(a<=l&&r<=b){
		Del(x);
		return;
	}
	Pushdown(x);
	int mid=(l+r)>>1,total=0;
	if(t[x].l)Delete(t[x].l,a,b,l,mid);
	if(t[x].r)Delete(t[x].r,a,b,mid+1,r);
	Pushup(x);
}
int Ask(int x,int y,int l,int r){
	if(l==r)return l;
	Pushdown(x);
	int mid=(l+r)>>1;
	if(y<=t[t[x].l].data)return Ask(t[x].l,y,l,mid);
	else return Ask(t[x].r,y-t[t[x].l].data,mid+1,r);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	m=read();
	for(int i=1;i<=m;i++){
		int op=read(),x=read(),y=0;
		if(op!=1&&op!=7)y=read();
		if(op==1){
			n++;fa[n]=n;
			Insert(rt[n],x,1,1,M);
		}
		if(op==2){
			x=Find(x);y=Find(y);
			if(x==y)continue;fa[y]=x;
			rt[x]=Merge(rt[x],rt[y]);
		}
		if(op==3){
			x=Find(x);
			int sum=Sum(rt[x],1,y,1,M);
			Delete(rt[x],1,y,1,M);
			Insert(rt[x],y,sum,1,M);
		}
		if(op==4){
			x=Find(x);
			int sum=Sum(rt[x],y,M,1,M);
			Delete(rt[x],y,M,1,M);
			Insert(rt[x],y,sum,1,M);
		}
		if(op==5){
			x=Find(x);
			printf("%d\n",Ask(rt[x],y,1,M));
		}
		if(op==6){
			x=Find(x);y=Find(y);
			printf("%d\n",t[rt[x]].sum>t[rt[y]].sum);
		}
		if(op==7){
			x=Find(x);
			printf("%d\n",t[rt[x]].data);
		}
	}
	return 0;
}
/*
9
1 2
1 3
1 4
1 5
1 6
2 1 2
2 3 2
2 4 5
5 2 3
*/