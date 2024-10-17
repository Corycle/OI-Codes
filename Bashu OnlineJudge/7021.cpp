/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<bitset>
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
const int N=1e5+5;
const int M=11;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bitset<N>F;
int n,m,tot,a[N],b[N*2],Ans[M];
struct Node{int op,x,y,val;}P[N];
struct Tree{int fa,sum,val,rev,ch[2],a[M];};
struct Splay_Tree{
	int Root;
	Tree t[N];
	void Reverse(int x){t[x].rev^=1;swap(t[x].ch[0],t[x].ch[1]);}
	void Pushdown(int x){if(t[x].rev){Reverse(t[x].ch[0]);Reverse(t[x].ch[1]);t[x].rev=0;}}
	void Pushup(int x){
		for(int i=1;i<=tot;i++)t[x].a[i]=t[t[x].ch[0]].a[i]+t[t[x].ch[1]].a[i];
		t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+1;
		t[x].a[t[x].val]++;
	}
	void Rotate(int x,int &f){
		int y=t[x].fa;int z=t[y].fa;
		int l=(x!=t[y].ch[0]),r=l^1;
		if(y!=f)t[z].ch[y!=t[z].ch[0]]=x;else f=x;
		t[x].fa=z;t[y].fa=x;t[t[x].ch[r]].fa=y;
		t[y].ch[l]=t[x].ch[r];t[x].ch[r]=y;
		Pushup(y);Pushup(x);
	}
	void Splay(int x,int &f){
		Pushdown(x);
		while(x!=f){
			int y=t[x].fa,z=t[y].fa;
			if(y!=f)Pushdown(z);Pushdown(y);Pushdown(x);
			if(y!=f){
				if((x==t[y].ch[0])^(y==t[z].ch[0]))Rotate(x,f);
				else Rotate(y,f);
			}
			Rotate(x,f);
		}
	}
	int Build(int l,int r){
		int x=(l+r)>>1;t[x].val=a[x];
		if(x!=l){t[x].ch[0]=Build(l,x-1);t[t[x].ch[0]].fa=x;}
		if(x!=r){t[x].ch[1]=Build(x+1,r);t[t[x].ch[1]].fa=x;}
		Pushup(x);
		return x;
	}
	int Find(int k){
		int x=Root;
		while(1){
			Pushdown(x);
			if(t[t[x].ch[0]].sum+1==k){Splay(x,Root);return x;}
			if(t[t[x].ch[0]].sum+1<k){k=k-t[t[x].ch[0]].sum-1;x=t[x].ch[1];}
			else x=t[x].ch[0];
		}
	}
	void Change(int k,int y){int x=Find(k);t[x].val=y;Pushup(x);}
	void Update(int l,int r){
		int x=Find(l-1),y=Find(r+1);Splay(x,Root);Splay(y,t[x].ch[1]);
		Reverse(t[y].ch[0]);
	}
	void Query(int l,int r){
		int x=Find(l-1),y=Find(r+1);Splay(x,Root);Splay(y,t[x].ch[1]);
		for(int i=1;i<=tot;i++)Ans[i]=t[t[y].ch[0]].a[i];
	}
}tree;
void Update(int x,int num,int val){
	for(int i=0;i<=20;i++){
		if((1<<i)<=num){
			num-=(1<<i);
			if(1ll*(1<<i)*x<=val)F|=(F<<((1<<i)*x));
		}
		else break;
	}
	if(num&&1ll*num*x<=val)F|=(F<<(num*x));
}
void Query(int l,int r,int val){
	F.reset();F[0]=1;tree.Query(l,r);
	for(int i=1;i<=tot;i++)Update(b[i],Ans[i],val);
	puts(F[val]?"Yes":"No");
}
int main(){
//	freopen("gym.in","r",stdin);
//	freopen("gym.out","w",stdout);
	n=read()+1;m=read();
	for(int i=2;i<=n;i++)a[i]=b[++b[0]]=read();
	for(int i=1;i<=m;i++){
		P[i].op=read();
		if(P[i].op==1){P[i].x=read()+1;P[i].y=b[++b[0]]=read();}
		if(P[i].op==2){P[i].x=read()+1;P[i].y=read()+1;}
		if(P[i].op==3){P[i].x=read()+1;P[i].y=read()+1;P[i].val=read();}
	}
	sort(b+1,b+b[0]+1);tot=unique(b+1,b+b[0]+1)-b-1;
	for(int i=2;i<=n;i++)a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
	for(int i=1;i<=m;i++)if(P[i].op==1)P[i].y=lower_bound(b+1,b+tot+1,P[i].y)-b;
	tree.Root=tree.Build(1,n+1);
	for(int i=1;i<=m;i++){
		if(P[i].op==1)tree.Change(P[i].x,P[i].y);
		if(P[i].op==2)tree.Update(P[i].x,P[i].y);
		if(P[i].op==3)Query(P[i].x,P[i].y,P[i].val);
	}
	return 0;
}