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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,root,tot;
struct tree{
	int l,r,num,data,fa;
}t[200005];
void Zig(int x){
	int y=t[x].fa;
	t[y].l=t[x].r;
	if(t[x].r)t[t[x].r].fa=y;
	t[x].fa=t[y].fa;
	if(t[y].fa){
		if(y==t[t[y].fa].l)t[t[y].fa].l=x;
		else t[t[y].fa].r=x;
	}
	t[x].r=y;
	t[y].fa=x;
}
void Zag(int x){
	int y=t[x].fa;
	t[y].r=t[x].l;
	if(t[x].l)t[t[x].l].fa=y;
	t[x].fa=t[y].fa;
	if(t[y].fa){
		if(y==t[t[y].fa].l)t[t[y].fa].l=x;
		else t[t[y].fa].r=x;
	}
	t[x].l=y;
	t[y].fa=x;
}
void Splay(int x){
	int p;
	while(t[x].fa){
		p=t[x].fa;
		if(t[p].fa==0){
			if(x==t[p].l)Zig(x);
			else Zag(x);
			break;
		}
		if(x==t[p].l){
			if(p==t[t[p].fa].l){Zig(p);Zig(x);}
			else{Zig(x);Zag(x);}
		}
		else{
			if(p==t[t[p].fa].l){Zag(x);Zig(x);}
			else{Zag(p);Zag(x);}
		}
	}
	root=x;
}
int Find(int x){
	int p=root;
	while(p){
		if(x==t[p].data){
			Splay(p);
			return 1;
		}
		if(x<=t[p].data)x=t[p].l;
		else x=t[p].r;
	}
	return 0;
}
void Insert(int x){
	int p=root,f=0;
	while(p){
		f=p;
		if(x==t[p].data){
			t[p].num++;
			return;
		}
		if(x<t[p].data)p=t[p].l;
		else p=t[p].r;
	}
	tot++;
	t[tot].data=x;
	t[tot].num=1;
	if(root==0){
		root=tot;
		return;
	}
	t[tot].fa=f;
	if(x<=t[f].data)t[f].l=tot;
	else t[f].r=tot;
	Splay(tot);
}
void bianli(int x){
	if(t[x].l)bianli(t[x].l);
	printf("%d %d\n",t[x].data,t[x].num);
	if(t[x].r)bianli(t[x].r);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int x=read();
		Insert(x);
	}
	bianli(root);
	return 0;
}