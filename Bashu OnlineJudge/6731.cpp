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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,Root[N];
int Rand(){return rand()*rand()+rand();}
struct Tree{
	int ch[2],fa,val,Max,sum,rnd;
	void Init(int x){val=Max=x;sum=1;rnd=Rand();}
};
struct Splay_Tree{
	int tot;
	Tree t[N*80];
	int NewNode(int x){tot++;t[tot].Init(x);return tot;}
	void Pushup(int x){
		if(!x)return;
		t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+1;
		t[x].Max=max(max(t[t[x].ch[0]].Max,t[t[x].ch[1]].Max),t[x].val);
	}
	void Split(int p,int k,int &x,int &y,int num){
		if(!p){x=y=0;return;}
		if(t[t[p].ch[0]].sum+num+1<=k){
			x=++tot;t[x]=t[p];Split(t[p].ch[1],k,t[x].ch[1],y,num+t[t[p].ch[0]].sum+1);
		}
		else{
			y=++tot;t[y]=t[p];Split(t[p].ch[0],k,x,t[y].ch[0],num);
		}
		Pushup(x);Pushup(y);
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		int p=++tot;
		if(t[x].rnd<t[y].rnd){
			t[p]=t[x];t[p].ch[1]=Merge(t[p].ch[1],y);
		}
		else{
			t[p]=t[y];t[p].ch[0]=Merge(x,t[p].ch[0]);
		}
		Pushup(p);
		return p;
	}
	int Insert(int p,int pos,int val){int x=0,y=0,z=NewNode(val);Split(p,pos-1,x,y,0);return Merge(Merge(x,z),y);}
	int Delete(int p,int pos){int x=0,y=0,z=0;Split(p,pos,x,y,0);Split(x,pos-1,x,z,0);return Merge(x,y);}
	int Query(int p,int l,int r){int x=0,y=0;Split(p,r,x,y,0);Split(x,l-1,x,y,0);return t[y].Max;}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();srand(time(NULL));
	for(int i=1;i<=n;i++)Root[0]=tree.Insert(Root[0],i,read());
	for(int i=1;i<=m;i++){
		int op=read();Root[i]=Root[i-1];int num=tree.t[Root[i]].sum;
		if(op==1){int x=(read()+Ans)%(num+1),v=read()^Ans;Root[i]=tree.Insert(Root[i],x+1,v);}
		if(op==2){int x=(read()+Ans)%num+1;Root[i]=tree.Delete(Root[i],x);}
		if(op==3){int l=(read()+Ans)%num+1,r=(read()+Ans*2)%num+1;if(l>r)swap(l,r);printf("%d\n",Ans=tree.Query(Root[i],l,r));}
		if(op==4){int k=(read()+Ans)%i;Root[i]=Root[k];}
	}
	return 0;
}