/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
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
const int N=100005;
const int M=11;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
char op[M];
double fac[M];
struct Tree{
	double P[M],F[M];
	int fa,aux,rev,ch[2];
	void Init(int type,double a,double b){
		if(type==1){
			double Sin=sin(b),Cos=cos(b);int f=1;
			for(int i=0;i<M;i++){
				P[i]=f*pow(a,i)*(i&1?Cos:Sin)/fac[i];
				if(i&1)f=-f;
			}
		}
		if(type==2){
			double E=exp(b);
			for(int i=0;i<M;i++)P[i]=pow(a,i)*E/fac[i];
		}
		if(type==3){
			memset(P,0,sizeof(P));
			P[0]=b;P[1]=a;
		}
		for(int i=0;i<M;i++)F[i]=P[i];
	}
	double Ask(double x){
		double ans=0;
		for(int i=M-1;i>=0;i--)ans=ans*x+F[i];
//		for(int i=0;i<M;i++)ans+=F[i]*pow(x,i);
		return ans;
	}
};
struct Link_Cut_Tree{
	Tree t[N];
	void Pushup(int x){
		for(int i=0;i<M;i++){
			t[x].F[i]=t[t[x].ch[0]].F[i]+t[t[x].ch[1]].F[i]+t[x].P[i];
		}
	}
	void Pushdown(int x){
		if(t[x].rev){
			t[x].rev=0;
			t[t[x].ch[0]].rev^=1;
			t[t[x].ch[1]].rev^=1;
			swap(t[x].ch[0],t[x].ch[1]);
		}
	}
	void Rotate(int x){
		int y=t[x].fa;int z=t[y].fa;
		int l=(x!=t[y].ch[0]),r=l^1;
		if(t[y].aux){
			if(y==t[z].ch[0])t[z].ch[0]=x;
			else t[z].ch[1]=x;
		}
		else{t[x].aux=0;t[y].aux=1;}
		t[x].fa=z;t[y].fa=x;
		t[t[x].ch[r]].fa=y;
		t[y].ch[l]=t[x].ch[r];
		t[x].ch[r]=y;
		Pushup(y);Pushup(x);
	}
	void Splay(int x){
		Pushdown(x);
		while(t[x].aux){
			int y=t[x].fa,z=t[y].fa;
			if(t[y].aux)Pushdown(z);
			Pushdown(y);Pushdown(x);
			if(t[y].aux){
				if((x==t[y].ch[0])^(y==t[z].ch[0]))Rotate(x);
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
			t[x].ch[1]=y;t[y].fa=x;
			t[t[x].ch[1]].aux=1;
			Pushup(x);y=x;x=t[x].fa;
		}
	}
	int Find(int x){
		Access(x);Splay(x);
		while(t[x].ch[0])x=t[x].ch[0];
		Splay(x);return x;
	}
	void Evert(int x){Access(x);Splay(x);t[x].rev^=1;}
	void Split(int x,int y){Evert(x);Access(y);Splay(y);}
	void Link(int x,int y){Evert(x);t[x].fa=y;}
	void Cut(int x,int y){Split(x,y);t[x].fa=t[x].aux=t[y].ch[0]=0;Pushup(y);}
	void Change(int x,int type,double a,double b){Evert(x);t[x].Init(type,a,b);}
	void Ask(int x,int y,double d){
		if(Find(x)!=Find(y))printf("unreachable\n");
		else{Split(x,y);printf("%.8e\n",t[y].Ask(d));}
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	fac[0]=1;
	for(int i=1;i<M;i++)fac[i]=fac[i-1]*i;
	n=read();m=read();read();
	for(int i=1;i<=n;i++){
		int type=read();
		double a=0,b=0;
		scanf("%lf%lf",&a,&b);
		tree.t[i].Init(type,a,b);
	}
	while(m--){
		scanf("%s",op);
		if(op[0]=='a')tree.Link(read()+1,read()+1);
		if(op[0]=='d')tree.Cut(read()+1,read()+1);
		if(op[0]=='t'){
			int x=read()+1,y=read()+1;
			double d=0;scanf("%lf",&d);
			tree.Ask(x,y,d);
		}
		if(op[0]=='m'){
			double a=0,b=0;
			int x=read()+1,type=read();
			scanf("%lf%lf",&a,&b);
			tree.Change(x,type,a,b);
		}
	}
	return 0;
}