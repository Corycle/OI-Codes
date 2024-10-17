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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
struct tree{
	int data,ch[2],sum,fa;
}t[N];
int fa[N];
int GetFather(int x){
	return x==fa[x]?x:fa[x]=GetFather(fa[x]);
}
void Pushup(int x){
	t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+1;
}
void Rotate(int x){
	int y=t[x].fa;int z=t[y].fa;
	int l=(x!=t[y].ch[0]);int r=l^1;
	if(z){
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
		if(z){
			if(x==t[y].ch[0]^y==t[z].ch[0])Rotate(x);
			else Rotate(y);
		}
		Rotate(x);
	}
}
void Insert(int x,int y){
	Splay(y);
	int p=y,f=0;
	while(p){
		f=p;t[p].sum++;
		if(t[x].data<=t[p].data)p=t[p].ch[0];
		else p=t[p].ch[1];
	}
	t[x].fa=f;
	if(t[x].data<=t[f].data)t[f].ch[0]=x;
	else t[f].ch[1]=x;
	Splay(x);
}
void Merge(int x,int y){
	if(t[x].ch[0])Merge(t[x].ch[0],y);
	if(t[x].ch[1])Merge(t[x].ch[1],y);
	t[x].ch[0]=t[x].ch[1]=0;
	t[x].sum=1;
	Insert(x,y);
}
void Link(int x,int y){
	int fx=GetFather(x),fy=GetFather(y);
	if(fx==fy)return;
	fa[fx]=fy;
	Splay(x);
	Splay(y);
	if(t[x].sum>t[y].sum)swap(x,y);
	Merge(x,y);
}
void Ask(int x,int k){
	Splay(x);
	if(k>t[x].sum){
		printf("-1\n");
		return;
	}
	while(1){
		if(k==t[t[x].ch[0]].sum+1){
			printf("%d\n",x);
			return;
		}
		if(k<=t[t[x].ch[0]].sum)x=t[x].ch[0];
		else{
			k=k-t[t[x].ch[0]].sum-1;
			x=t[x].ch[1];
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		fa[i]=i;
		t[i].sum=1;
		t[i].data=read();
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Link(x,y);
	}
	m=read();
	while(m--){
		char op[2];
		scanf("%s",op);
		int x=read(),y=read();
		if(op[0]=='B')Link(x,y);
		if(op[0]=='Q')Ask(x,y);
	}
	return 0;
}