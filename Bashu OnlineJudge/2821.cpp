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
int n,m;
struct tree{
	int fa,data;
	int rev,aux;
	int ch[2];
}t[10005];
void Pushdown(int x){
	if(t[x].rev){
		t[x].rev^=1;
		t[t[x].ch[0]].rev^=1;
		t[t[x].ch[1]].rev^=1;
		swap(t[x].ch[0],t[x].ch[1]);
	}
}
void Rotate(int x){
	int y=t[x].fa;int z=t[y].fa;
	int l=(x!=t[y].ch[0]);int r=l^1;
	if(t[y].aux){
		if(y==t[z].ch[0])t[z].ch[0]=x;
		else t[z].ch[1]=x;
	}
	else{
		t[y].aux=1;
		t[x].aux=0;
	}
	t[x].fa=z;t[y].fa=x;
	t[t[x].ch[r]].fa=y;
	t[y].ch[l]=t[x].ch[r];
	t[x].ch[r]=y;
}
void Splay(int x){
	Pushdown(x);
	while(t[x].aux){
		int y=t[x].fa;int z=t[y].fa;
		if(t[y].aux)Pushdown(z);
		Pushdown(y);Pushdown(x);
		if(t[y].aux){
			if(t[y].ch[0]==x^t[z].ch[0]==y)Rotate(x);
			else Rotate(y);
		}
		Rotate(x);
	}
}
void Access(int x){
	int y=0;
	while(x){
		Splay(x);
		t[t[x].ch[1]].aux=0;
		t[y].aux=1;
		t[x].ch[1]=y;
		t[y].fa=x;
		y=x;
		x=t[x].fa;
	}
}
int Findroot(int x){
	Access(x);
	Splay(x);
	while(t[x].ch[0]){
		Pushdown(x);
		x=t[x].ch[0];
	}
	return x;
}
void Evert(int x){
	Access(x);
	Splay(x);
	t[x].rev^=1;
}
void Cut(int x,int y){
	Evert(x);
	Access(y);
	Splay(y);
	t[t[y].ch[0]].fa=0;
	t[t[y].ch[0]].aux=0;
	t[y].ch[0]=0;
}
void Link(int x,int y){
	Evert(y);
	t[y].fa=x;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	while(m--){
		char s[10];
		scanf("%s",s);
		int x=read(),y=read();
		if(s[0]=='C')Link(x,y);
		if(s[0]=='D')Cut(x,y);
		if(s[0]=='Q'){
			if(Findroot(x)==Findroot(y))printf("Yes\n");
			else printf("No\n");
		}
	}
	return 0;
}