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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int mod=10000;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,fl,tot,root;
struct treap{
	int data,sum,pro;
	int l,r;
}t[3000005];
void Pushup(int x){
	t[x].sum=t[t[x].l].sum+t[t[x].r].sum+1;
}
void Zig(int &p){
	int v=t[p].l;
	t[p].l=t[v].r;
	t[v].r=p;
	Pushup(p);Pushup(v);
	p=v;
}
void Zag(int &p){
	int v=t[p].r;
	t[p].r=t[v].l;
	t[v].l=p;
	Pushup(p);Pushup(v);
	p=v;
}
void Insert(int &p,int x){
	if(p==0){
		tot++;p=tot;
		t[p].data=x;
		t[p].sum=1;
		t[p].pro=rand()%mod;
		return;
	}
	t[p].sum++;
	if(x<t[p].data){
		Insert(t[p].l,x);
		if(t[t[p].l].pro<t[p].pro)Zig(p);
	}
	if(x>t[p].data){
		Insert(t[p].r,x);
		if(t[t[p].r].pro<t[p].pro)Zag(p);
	}
}
void Delete(int &p,int x){
	if(p==0)return;
	if(x<t[p].data){t[p].sum--;Delete(t[p].l,x);}
	if(x>t[p].data){t[p].sum--;Delete(t[p].r,x);}
	if(x==t[p].data){
		if(!t[p].l&&!t[p].r){p=0;return;}
		int lp=t[p].l?t[t[p].l].pro:inf;
		int rp=t[p].r?t[t[p].r].pro:inf;
		if(lp<=rp){Zig(p);t[p].sum--;Delete(t[p].r,x);}
		else{Zag(p);t[p].sum--;Delete(t[p].l,x);}
	}
}
int Find(int k){
	int p=root;
	while(p){
		if(k==t[t[p].l].sum+1)return t[p].data;
		if(k<=t[t[p].l].sum)p=t[p].l;
		else{
			k=k-t[t[p].l].sum-1;
			p=t[p].r;
		}
	}
	return 0;
}
void FIND(int x){
	int p=root;fl=0;
	while(p){
		if(x==t[p].data){fl=1;return;}
		if(x<t[p].data)p=t[p].l;
		else p=t[p].r;
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	srand(time(NULL));
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int x=read();
		FIND(x);
		if(fl==0)Insert(root,x);
	}
	while(m--){
		int p=read(),x=read();
		if(p==1||p==2)FIND(x);
		if(p==1&&fl==0)Insert(root,x);
		if(p==2&&fl==1)Delete(root,x);
		if(p==3)printf("%d\n",Find(x));
	}
	return 0;
}
/*
10 3
1 1 2 2 2 3 3 5 5 9
3 5
1 4
3 4
*/