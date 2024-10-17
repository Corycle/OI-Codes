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
int n,m,root,tot;
struct tree{
	int data,pos,fa,rev;
	int maxx,sum,num;
	int ch[2];
}t[100005];
void Pushup(int x){
	int l=t[x].ch[0],r=t[x].ch[1];
	t[x].maxx=max(t[x].data,max(t[l].maxx,t[r].maxx));
	t[x].sum=t[l].sum+t[r].sum+t[x].data;
	t[x].num=t[l].num+t[r].num+1;
}
void Pushdown(int x){
	int l=t[x].ch[0],r=t[x].ch[1];
	if(t[x].rev){
		t[x].rev^=1;
		t[l].rev^=1;
		t[r].rev^=1;
		swap(t[x].ch[0],t[x].ch[1]);
	}
}
void Rotate(int x,int &f){
	int y=t[x].fa;int z=t[y].fa;
	int l=(x!=t[y].ch[0]);int r=l^1;
	if(y==f)f=x;
	else{
		if(y==t[z].ch[0])t[z].ch[0]=x;
		else t[z].ch[1]=x;
	}
	t[x].fa=z;t[y].fa=x;
	t[t[x].ch[r]].fa=y;
	t[y].ch[l]=t[x].ch[r];
	t[x].ch[r]=y;
	Pushup(y);Pushup(x);
}
void Splay(int x,int &f){
	while(x!=f){
		int y=t[x].fa;int z=t[y].fa;
		if(y!=f){
			if(t[y].ch[0]==x^t[z].ch[0]==y)Rotate(x,f);
			else Rotate(y,f);
		}
		Rotate(x,f);
	}
}
void Insert(int pos,int x){
	int p=root,f=0;
	while(p){
		f=p;
		t[p].maxx=max(t[p].maxx,x);
		t[p].sum+=x;t[p].num++;
		if(pos<=t[p].pos)p=t[p].ch[0];
		else p=t[p].ch[1];
	}
	tot++;
	t[tot].num=1;
	t[tot].sum=x;
	t[tot].data=x;
	t[tot].maxx=x;
	t[tot].pos=pos;
	if(root==0){
		root=tot;
		return;
	}
	t[tot].fa=f;
	if(t[tot].pos<=t[f].pos)t[f].ch[0]=tot;
	else t[f].ch[1]=tot;
	Splay(tot,root);
}
int Find(int x){
	int p=root;
	while(p){
		Pushdown(p);
		if(t[t[p].ch[0]].num+1==x)return p;
		if(t[t[p].ch[0]].num>=x)p=t[p].ch[0];
		else{
			x=x-t[t[p].ch[0]].num-1;
			p=t[p].ch[1];
		}
	}
}
void Ask(int x){
	int p=Find(x+1);
	printf("%d\n",t[p].data);
}
void Add(int k,int x){
	int p=Find(k+1);
	Splay(p,root);
	t[p].data+=x;
	t[p].sum+=x;
}
void Sum(int l,int r){
	int x=Find(l),y=Find(r+2);
	Splay(x,root);
	Splay(y,t[root].ch[1]);
	printf("%d\n",t[t[y].ch[0]].sum);
}
void Max(int l,int r){
	int x=Find(l),y=Find(r+2);
	Splay(x,root);
	Splay(y,t[root].ch[1]);
	printf("%d\n",t[t[y].ch[0]].maxx);
}
void Rev(int l,int r){
	int x=Find(l),y=Find(r+2);
	Splay(x,root);
	Splay(y,t[root].ch[1]);
	t[t[y].ch[0]].rev^=1;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int x=read();
		Insert(i+1,x);
	}
	Insert(1,0);
	Insert(n+2,0);
	while(m--){
		int p=read(),x=read();
		if(p==1){
			Ask(x);
			continue;
		}
		int y=read();
		if(p==2)Add(x,y);
		if(p==3)Sum(x,y);
		if(p==4)Max(x,y);
		if(p==5)Rev(x,y);
	}
	return 0;
}