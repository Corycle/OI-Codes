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
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Root[N];
struct Tree{int ch[2],val,rnd,sum;};
struct Treap{
	int tot;
	Tree t[N*40];
	int NewNode(int x){tot++;t[tot].val=x;t[tot].rnd=rand();t[tot].sum=1;return tot;}
	void Pushup(int x){if(x)t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+1;}
	void Split(int p,int k,int &x,int &y,int num){
		if(!p){x=0;y=0;return;}
		if(t[t[p].ch[0]].sum+num+1<=k){
			x=++tot;t[x]=t[p];
			Split(t[p].ch[1],k,t[x].ch[1],y,t[t[p].ch[0]].sum+num+1);
		}
		else{
			y=++tot;t[y]=t[p];
			Split(t[p].ch[0],k,x,t[y].ch[0],num);
		}
		Pushup(x);Pushup(y);
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		int p=++tot;
		if(t[x].rnd<=t[y].rnd){
			t[p]=t[x];
			t[p].ch[1]=Merge(t[p].ch[1],y);
		}
		else{
			t[p]=t[y];
			t[p].ch[0]=Merge(x,t[p].ch[0]);
		}
		Pushup(p);
		return p;
	}
	void Insert(int &rt,int k,int val){int x=0,y=0,z=NewNode(val);Split(rt,k-1,x,y,0);rt=Merge(Merge(x,z),y);}
	void Delete(int &rt,int k){int x=0,y=0,z=0;Split(rt,k,x,y,0);Split(x,k-1,x,z,0);rt=Merge(x,y);}
	int Query(int &rt,int k){int x=0,y=0,z=0;Split(rt,k,x,y,0);Split(x,k-1,x,z,0);return t[z].val;}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int op=read(),t=read(),k=read();
		if(op==1){Root[++cnt]=Root[t],tree.Insert(Root[cnt],k,read());}
		if(op==2){Root[++cnt]=Root[t],tree.Delete(Root[cnt],k);}
		if(op==3)printf("%d\n",tree.Query(Root[t],k));
	}
	return 0;
}