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
int n,root,tot,minn,sum;
struct tree{
	int data;
	int fa,l,r;
	int ln,rn,num;
}t[100005];
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
	t[y].ln=t[x].rn;
	t[x].rn=t[y].ln+t[y].rn+1;
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
	t[y].rn=t[x].ln;
	t[x].ln=t[y].ln+t[y].rn+1;
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
void Insert(int x){
	int p=root,f=0;
	while(p){
		f=p;
		if(x<=t[p].data){
			t[p].ln++;
			p=t[p].l;
		}
		else{
			t[p].rn++;
			p=t[p].r;
		}
	}
	tot++;
	t[tot].data=x;
	if(root==0){
		root=tot;
		return;
	}
	t[tot].fa=f;
	if(x<=t[f].data)t[f].l=tot;
	else t[f].r=tot;
	Splay(tot);
}
int Ask(int x){
	while(t[x].l)x=t[x].l;
	return x;
}
int Find(int x){
	int p=root;
	while(p){
		if(x==t[p].data){
			Splay(p);
			return 1;
		}
		if(x<=t[p].data)p=t[p].l;
		else p=t[p].r;
	}
	return 0;
}
void Delete(int x){
	Find(x);
	int p=root;
	int ls=t[p].l,rs=t[p].r;
	if(!ls&&!rs){
		root=0;
		return;
	}
	if(!ls){
		root=rs;
		t[rs].fa=0;
		return;
	}
	if(!rs){
		root=ls;
		t[ls].fa=0;
		return;
	}
	p=ls;
	t[ls].fa=0;
	while(t[p].r)p=t[p].r;
	Splay(p);
	t[p].r=rs;
	t[rs].fa=p;
	t[p].rn=t[rs].ln+t[rs].rn+1;
}
int FIND(int k){
	int p=root;
	if(t[p].ln+t[p].rn+1<k)return -1;
	while(1){
		if(t[p].rn+1==k)return t[p].data;
		if(t[p].rn>=k)p=t[p].r;
		else{
			k=k-t[p].rn-1;
			p=t[p].l;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();minn=read();
	int cnt=0;
	for(int i=1;i<=n;i++){
		char s[5];
		scanf("%s",s+1);
		int x=read();
		if(s[1]=='A')sum+=x;
		if(s[1]=='S'){
			sum-=x;
			Insert(minn-sum);
			cnt+=t[root].ln;
			root=t[root].r;
			t[root].fa=0;
		}
		if(s[1]=='I'){
			if(x>=minn)Insert(x-sum);
		}
		if(s[1]=='F'){
			int y=FIND(x);
			if(y!=-1)y+=sum;
			printf("%d\n",y);
		}
	}
	printf("%d",cnt);
	return 0;
}