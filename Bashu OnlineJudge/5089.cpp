/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=5000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,st,ed,Lpos,Rpos;
struct Splay_Tree{
	int tot,top,root,Stack[N];
	struct Tree{int ch[2],fa,rev,sum;char data;}t[N];
	void Clear(int x){
		Stack[++top]=x;
		t[x].sum=t[x].data=t[x].rev=0;
		t[x].ch[0]=t[x].ch[1]=t[x].fa=0;
	}
	int NewPoint(){return top?Stack[top--]:++tot;}
	void Pushup(int x){
		t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+1;
	}
	void Pushdown(int x){
		if(t[x].rev){
			t[x].rev^=1;
			t[t[x].ch[0]].rev^=1;
			t[t[x].ch[1]].rev^=1;
			swap(t[x].ch[0],t[x].ch[1]);
		}
	}
	void Rotate(int x,int &f){
		int y=t[x].fa;int z=t[y].fa;
		int l=(x!=t[y].ch[0]);int r=l^1;
		if(y!=f){
			if(y==t[z].ch[0])t[z].ch[0]=x;
			else t[z].ch[1]=x;
		}
		else f=x;
		t[x].fa=z;t[y].fa=x;
		t[t[x].ch[r]].fa=y;
		t[y].ch[l]=t[x].ch[r];
		t[x].ch[r]=y;
		Pushup(y);Pushup(x);
	}
	void Splay(int x,int &f){
		Pushdown(x);
		while(x!=f){
			int y=t[x].fa;int z=t[y].fa;
			if(y!=f)Pushdown(z);
			Pushdown(y);Pushdown(x);
			if(y!=f){
				if((x==t[y].ch[0])^(y==t[z].ch[0]))Rotate(x,f);
				else Rotate(y,f);
			}
			Rotate(x,f);
		}
	}
	int Build(int l,int r){
		int mid=(l+r)>>1;t[mid].data=s[mid-1];
		if(l<=mid-1)t[mid].ch[0]=Build(l,mid-1);
		if(mid+1<=r)t[mid].ch[1]=Build(mid+1,r);
		t[t[mid].ch[0]].fa=t[t[mid].ch[1]].fa=mid;
		Pushup(mid);return mid;
	}
	int Find(int k){
		int p=root;
		while(1){
			Pushdown(p);
			if(k==t[t[p].ch[0]].sum+1)return p;
			if(k<=t[t[p].ch[0]].sum)p=t[p].ch[0];
			else{k-=t[t[p].ch[0]].sum+1;p=t[p].ch[1];}
		}
	}
	void Insert(int pos,char c){
		int x=NewPoint();t[x].data=c;
		int p=Find(pos+1);Splay(p,root);
		Pushdown(p);p=t[p].ch[1];Pushdown(p);
		while(t[p].ch[0]){Pushdown(t[p].ch[0]);p=t[p].ch[0];}
		t[p].ch[0]=x;t[x].fa=p;Pushup(p);Splay(x,root);
	}
	void Delete(int pos){
		int x=Find(pos+1);Splay(x,root);
		int l=t[x].ch[0],r=t[x].ch[1];
		Pushdown(l);t[l].fa=0;
		Pushdown(r);t[r].fa=0;
		int y=r;root=l;Clear(x);
		while(t[l].ch[1]){l=t[l].ch[1];Pushdown(l);}
		while(t[r].ch[0]){r=t[r].ch[0];Pushdown(r);}
		Splay(r,y);Splay(l,root);
		t[r].fa=l;t[l].ch[1]=r;
		Pushup(l);
	}
	void Reverse(int l,int r){
		int x=Find(l),y=Find(r+2);
		Splay(x,root);Splay(y,t[x].ch[1]);
		t[t[y].ch[0]].rev^=1;
	}
	void Print(int x){
		Pushdown(x);
		if(t[x].ch[0])Print(t[x].ch[0]);
		if(x!=st&&x!=ed)printf("%c",t[x].data);
		if(t[x].ch[1])Print(t[x].ch[1]);
	}
}tree;
void Move_Left(){
	char w[2];scanf("%s",w);
	if(w[0]=='L')if(Lpos==0)puts("F");else{Lpos--;puts("T");}
	if(w[0]=='R')if(Rpos==0)puts("F");else{Rpos--;puts("T");}
}
void Move_Right(){
	char w[2];scanf("%s",w);
	if(w[0]=='L')if(Lpos==n)puts("F");else{Lpos++;puts("T");}
	if(w[0]=='R')if(Rpos==n)puts("F");else{Rpos++;puts("T");}
}
void Insert(){
	char w[2],c[2];scanf("%s%s",w,c);n++;puts("T");
	if(w[0]=='L'){tree.Insert(Lpos,c[0]);if(Lpos<=Rpos)Rpos++;Lpos++;}
	if(w[0]=='R'){tree.Insert(Rpos,c[0]);if(Rpos<=Lpos)Lpos++;Rpos++;}
}
void Delete(){
	char w[2];scanf("%s",w);
	if(w[0]=='L')if(Lpos==n)puts("F");else{n--;tree.Delete(Lpos+1);if(Lpos<Rpos)Rpos--;puts("T");}
	if(w[0]=='R')if(Rpos==n)puts("F");else{n--;tree.Delete(Rpos+1);if(Rpos<Lpos)Lpos--;puts("T");}
}
void Reverse(){
	if(Rpos<=Lpos)puts("F");
	else{tree.Reverse(Lpos+1,Rpos);puts("T");}
}
void Show(){tree.Print(tree.root);puts("");}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	tree.root=tree.Build(1,n+2);
	Lpos=0;Rpos=n;st=1;ed=n+2;
	tree.tot=ed;m=read();
	while(m--){
		char op[2];scanf("%s",op);
		if(op[0]=='<')Move_Left();
		if(op[0]=='>')Move_Right();
		if(op[0]=='I')Insert();
		if(op[0]=='D')Delete();
		if(op[0]=='R')Reverse();
		if(op[0]=='S')Show();
	}
	return 0;
}