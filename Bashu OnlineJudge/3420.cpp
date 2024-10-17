#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,c,p;
int a[N],d[N][15];
struct Link_Cut_Tree{
	struct Tree{
		int ch[2],fa,aux,rev,Max;
	}t[N];
	int Pushup(int x){
		t[x].Max=max(a[x],max(t[t[x].ch[0]].Max,t[t[x].ch[1]].Max));
	}
	int Pushdown(int x){
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
			t[x].aux=0;t[y].aux=1;
		}
		t[x].fa=z;t[y].fa=x;
		t[t[x].ch[r]].fa=y;
		t[y].ch[l]=t[x].ch[r];
		t[x].ch[r]=y;
		Pushup(y);Pushup(x);
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
			t[x].ch[1]=y;
			t[y].aux=1;
			t[y].fa=x;
			Pushup(x);
			y=x;x=t[x].fa;
		}
	}
	int Find(int x){
		Access(x);Splay(x);
		while(t[x].ch[0])x=t[x].ch[0];
		return x;
	}
	void Evert(int x){Access(x);Splay(x);t[x].rev^=1;}
	void Split(int x,int y){Evert(x);Access(y);Splay(y);}
	void Link(int x,int y){Evert(x);t[x].fa=y;}
	void Cut(int x,int y){Split(x,y);t[x].aux=t[x].fa=t[y].ch[0]=0;Pushup(y);}
	void Change(int x,int y){Access(x);Splay(x);a[x]=y;Pushup(x);}
}Tree[15];
void Update(int x,int y,int z){
	for(int i=1;i<=c;i++){
		if(Tree[i].Find(x)==Tree[i].Find(y)){
			Tree[i].Split(x,y);
			if(Tree[i].t[y].ch[0]!=x||Tree[i].t[x].ch[1])continue;
			//x和y相连但没有这条边 
			if(i==z){
				printf("Success.\n");return;
			}
			if(d[x][z]>1||d[y][z]>1){
				printf("Error 1.\n");return;
			}
			if(Tree[z].Find(x)==Tree[z].Find(y)){
				printf("Error 2.\n");return;
			}
			Tree[i].Cut(x,y);
			Tree[z].Link(x,y);
			d[x][i]--;d[y][i]--;
			d[x][z]++;d[y][z]++;
			printf("Success.\n");
			return;
		}
	}
	printf("No such edge.\n");
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();c=read();p=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		for(int j=1;j<=c;j++){
			Tree[j].t[i].Max=a[i];
		}
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read()+1;
		d[x][z]++;d[y][z]++;
		Tree[z].Link(x,y);
	}
	while(p--){
		int op=read();
		if(op==0){
			int x=read(),y=read();
			for(int j=1;j<=c;j++){
				Tree[j].Change(x,y);
			}
		}
		if(op==1){
			int x=read(),y=read(),z=read()+1;
			Update(x,y,z);
		}
		if(op==2){
			int z=read()+1,x=read(),y=read();
			if(Tree[z].Find(x)!=Tree[z].Find(y))printf("-1\n");
			else{
				Tree[z].Split(x,y);
				printf("%d\n",Tree[z].t[y].Max);
			}
		}
	}
	return 0;
}