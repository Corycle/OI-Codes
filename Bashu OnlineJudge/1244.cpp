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
const int N=80005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N],tot,root,ans[N];
struct tree{
	int fa,data,sum;
	int ch[2];
}t[N];
void Pushup(int x){
	t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+1;
}
void Rotate(int x){
	int y=t[x].fa;int z=t[y].fa;
	int l=(x!=t[y].ch[0]);int r=l^1;
	if(z!=0){
		if(y==t[z].ch[0])t[z].ch[0]=x;
		else t[z].ch[1]=x;
	}
	t[x].fa=z;t[y].fa=x;
	t[t[x].ch[r]].fa=y;
	t[y].ch[l]=t[x].ch[r];
	t[x].ch[r]=y;
	Pushup(y);Pushup(x);
}
void Splay(int x){
	while(t[x].fa){
		int y=t[x].fa;int z=t[y].fa;
		if(z!=0){
			if(x==t[y].ch[0]^y==t[z].ch[0])Rotate(x);
			else Rotate(y);
		}
		Rotate(x);
	}
	root=x;
}
void Insert(int x){
	int p=root,f=0;
	while(p){
		f=p;
		if(x<=t[p].data)p=t[p].ch[0];
		else p=t[p].ch[1];
	}
	tot++;
	t[tot].data=x;
	t[tot].sum=1;
	if(root==0){
		root=tot;
		return;
	}
	t[tot].fa=f;
	if(x<=t[f].data)t[f].ch[0]=tot;
	else t[f].ch[1]=tot;
	Splay(tot);
}
int Find(int k){
	int p=root;
	while(1){
		if(k==t[t[p].ch[0]].sum+1){
			Splay(p);
			return t[p].data;
		}
		if(k<=t[t[p].ch[0]].sum)p=t[p].ch[0];
		else{
			k-=t[t[p].ch[0]].sum+1;
			p=t[p].ch[1];
		}
	}
}
void Delete(int x){
	int p=root;
	int ls=t[p].ch[0],rs=t[p].ch[1];
	if(!ls&&!rs){
		root=0;
		return;
	}
	if(!ls||!rs){
		root=max(ls,rs);
		t[root].fa=0;
		return;
	}
	p=ls;
	t[p].fa=0;
	while(t[p].ch[1])p=t[p].ch[1];
	Splay(p);
	t[p].ch[1]=rs;
	t[rs].fa=p;
	Pushup(rs);Pushup(p);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	Insert(1);
	for(int i=2;i<=n;i++){
		a[i]=read();
		Insert(i);
	}
	for(int i=n;i>=1;i--){
		ans[i]=Find(a[i]+1);
		Delete(root);
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}