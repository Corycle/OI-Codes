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
int n,a[30005],root,tot;
struct tree{
	int sum,num,data,fa;
	int ch[2];
}t[80005];
void Pushup(int x){
	t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+t[x].num;
}
void Rotate(int x){
	int y=t[x].fa;int z=t[y].fa;
	int l=(x!=t[y].ch[0]);int r=l^1;
	if(z!=0){
		if(t[z].ch[0]==y)t[z].ch[0]=x;
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
		t[p].sum++;
		if(x<=t[p].data)p=t[p].ch[0];
		else p=t[p].ch[1];
	}
	tot++;
	t[tot].data=x;
	t[tot].num=t[tot].sum=1;
	if(root==0){
		root=tot;
		return;
	}
	t[tot].fa=f;
	if(x<=t[f].data)t[f].ch[0]=tot;
	else t[f].ch[1]=tot;
	Splay(tot);
}
int FIND(int k){
	int p=root;
	if(t[p].sum<k)return -1;
	while(1){
		if(t[p].sum-t[t[p].ch[0]].sum==k)return t[p].data;
		if(t[t[p].ch[1]].sum>=k)p=t[p].ch[1];
		else{
			k=k-t[t[p].ch[1]].sum-1;
			p=t[p].ch[0];
		}
	}
}
int Find(int x){
	int p=root;
	while(p){
		if(x==t[p].data){
			Splay(p);
			return 1;
		}
		if(x<=t[p].data) p=t[p].ch[0];
		else p=t[p].ch[1];
	}
	return 0;
}
void Delete(int x){
	Find(x);
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
	for(int i=1;i<=n;i++){
		a[i]=read();
		Insert(a[i]);
	}
	int m=read();
	while(m--){
		char s[2];
		scanf("%s",s+1);
		if(s[1]=='Q'){
			int x=read();
			printf("%d\n",FIND(x));
		}
		if(s[1]=='A'){
			int x=read(),y=read();
			Delete(a[x]);
			a[x]-=y;
			if(a[x]>0)Insert(a[x]);
		}
		if(s[1]=='C'){
			int x=read(),y=read();
			Delete(a[x]);
			a[x]+=y;
			Insert(a[x]);
		}
	}
	printf("%d",t[root].sum);
	return 0;
}