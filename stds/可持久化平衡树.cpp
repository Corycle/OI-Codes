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
#define re register int
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=2147483647;
const int N=500005;
inline int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int root[N],cnt=1;
struct Tree{
	int pro,data,sum;
    int ch[2];
}t[N*50];
inline int New(int x){
	t[++cnt].data=x;
	t[cnt].sum=1;
	t[cnt].pro=rand();
	return cnt;
}
inline void Pushup(int x){
	if(!x)return;
	t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+1;
}
inline void Split(int p,int k,int &x,int &y){
	if(!p){
		x=y=0;
		return;
	}
	cnt++;
	if(t[p].data<=k){
		x=cnt;t[x]=t[p];
		Split(t[x].ch[1],k,t[x].ch[1],y);
	}
	else{
		y=cnt;t[y]=t[p];
		Split(t[y].ch[0],k,x,t[y].ch[0]);
	}
	Pushup(x);Pushup(y);
}
inline int Merge(int x,int y){
	if(!x||!y)return x+y;
	int z=++cnt;
	if(t[x].pro<t[y].pro){
		t[z]=t[x];
		t[z].ch[1]=Merge(t[z].ch[1],y);
	}
	else{
		t[z]=t[y];
		t[z].ch[0]=Merge(x,t[z].ch[0]);
	}
	Pushup(z);
	return z;
}
inline void Insert(int b,int data){
	int x=0,y=0,z=0;
	Split(root[b],data,x,y);
	z=New(data);
	root[b]=Merge(Merge(x,z),y);
}
inline void Delete(int b,int data){
	int x=0,y=0,z=0;
	Split(root[b],data,x,z);
    Split(x,data-1,x,y);
    y=Merge(t[y].ch[0],t[y].ch[1]);
    root[b]=Merge(Merge(x,y),z);
}
inline int Pos(int p,int k){
	while(1){
		if(k==t[t[p].ch[0]].sum+1)return p;
		if(k<=t[t[p].ch[0]].sum+1)p=t[p].ch[0];
		else{
			k-=t[t[p].ch[0]].sum+1;
			p=t[p].ch[1];
		}
	}
}
inline int Find(int b,int k){
	int x=0,y=0;
	Split(root[b],k-1,x,y);
	return t[x].sum+1;
}
inline int Ask(int p,int k){
	int x=Pos(p,k);
	return t[x].data;
}
inline int Pred(int b,int data){
	int x=0,y=0;
	Split(root[b],data-1,x,y);
	if(!x)return -inf;
	return Ask(x,t[x].sum);
}
inline int Succ(int b,int data){
	int x=0,y=0;
	Split(root[b],data,x,y);
	if(!y)return inf;
	return Ask(y,1);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
//	srand(time(NULL));
	int n=read();
	for(re i=1;i<=n;i++){
		int lst=read(),op=read(),x=read();
		root[i]=root[lst];
		if(op==1)Insert(i,x);
		if(op==2)Delete(i,x);
		if(op==3)printf("%d\n",Find(i,x));
		if(op==4)printf("%d\n",Ask(root[i],x));
		if(op==5)printf("%d\n",Pred(i,x));
		if(op==6)printf("%d\n",Succ(i,x));
	}
	return 0;
}
