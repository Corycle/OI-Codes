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
	int fa,bj,data;
	int aux,rev,sum;
	int ch[2],lc,rc;
}t[100005];
void Pushdown(int x){
	int l=t[x].ch[0],r=t[x].ch[1];
	if(t[x].rev){
		t[x].rev^=1;
		t[l].rev^=1;
		t[r].rev^=1;
		swap(t[x].lc,t[x].rc);
		swap(t[x].ch[0],t[x].ch[1]);
	}
	if(t[x].bj){
		t[x].sum=1;
		t[x].data=t[x].bj;
		t[x].lc=t[x].rc=t[x].bj;
		t[l].bj=t[r].bj=t[x].bj;
		t[x].bj=0;
	}
}
void Pushup(int x){
	int l=t[x].ch[0],r=t[x].ch[1];
	t[x].sum=1;
	if(l){
		Pushdown(l);
		t[x].sum+=t[l].sum-(t[l].rc==t[x].data);
		t[x].lc=t[l].lc;
	}
	else t[x].lc=t[x].data;
	if(r){
		Pushdown(r);
		t[x].sum+=t[r].sum-(t[r].lc==t[x].data);
		t[x].rc=t[r].rc;
	}
	else t[x].rc=t[x].data;
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
	Pushup(y);
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
	Pushup(x);
}
void Access(int x){
	int y=0;
	while(x){
		Splay(x);
		t[t[x].ch[1]].aux=0;
		t[x].ch[1]=y;
		t[y].aux=1;
		t[y].fa=x;
		Pushup(x);
		y=x;
		x=t[x].fa;
	}
}
void Evert(int x){
	Access(x);
	Splay(x);
	t[x].rev^=1;
}
void Link(int x,int y){
	Evert(y);
	t[y].fa=x;
}
void Change(int x,int y,int z){
	Evert(x);
	Access(y);
	Splay(y);
	t[y].bj=z;
}
void Sum(int x,int y){
	Evert(x);
	Access(y);
	Splay(y);
	printf("%d\n",t[y].sum);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int x=read();
		t[i].sum=1;
		t[i].data=x;
		t[i].lc=t[i].rc=x;
	}
	for(int i=1;i<=n-1;i++){
		int x=read(),y=read();
		Link(x,y);
	}
	while(m--){
		char s[2];
		scanf("%s",s);
		if(s[0]=='Q'){
			int x=read(),y=read();
			Sum(x,y);
		}
		if(s[0]=='C'){
			int x=read(),y=read(),z=read();
			Change(x,y,z);
		}
	}
	return 0;
}