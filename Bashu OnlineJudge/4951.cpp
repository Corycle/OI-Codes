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
#include<set>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
#define set_it set<int>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,b[N];
struct Node{int op,x;}P[N];
struct Segment_Tree{
	int t[N*4];
	void Update(int x,int y,int val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p]+=val;return;}
		int mid=(l+r)>>1;
		Update(x,y,val,lson);Update(x,y,val,rson);
	}
	int Query(int x,int p,int l,int r){
		if(x<l||x>r)return 0;
		if(l==r)return t[p];
		int mid=(l+r)>>1;
		return Query(x,lson)+Query(x,rson)+t[p];
	}
	void Change(int x,int y){
		Update(x,x,y-Query(x,1,1,tot),1,1,tot);
	}
}tree;
set<int>S;
struct Spaly{int ch[2],fa;};
struct Spaly_Tree{
	int Root;
	Spaly t[N];
	int Ins(int p,int x){
		t[x].fa=p;
		if(x<p)t[p].ch[0]=x;
		if(x>p)t[p].ch[1]=x;
		int dep=tree.Query(p,1,1,tot)+1;
		tree.Change(x,dep);
		return dep;
	}
	int Insert(int x){
		S.insert(x);
		if(!Root){Root=x;tree.Change(x,1);return 1;}
		set_it p=S.lower_bound(x),l=S.begin(),r=--S.end();
		if(p==l)return Ins((*(++p)),x);
		if(p==r)return Ins((*(--p)),x);
		l=--p;r=++++p;--p;
		if(!t[(*l)].ch[1])return Ins((*l),x);
		if(!t[(*r)].ch[0])return Ins((*r),x);
		return -1;
	}
	int SpalyMin(){
		set_it p=S.begin();
		int x=(*p),dep=tree.Query(x,1,1,tot);
		if(x==Root)return 1;
		tree.Change(x,1);
		tree.Update(t[x].fa,tot,1,1,1,tot);
		t[t[x].fa].ch[0]=t[x].ch[1];
		t[t[x].ch[1]].fa=t[x].fa;
		t[x].ch[1]=Root;t[Root].fa=x;
		t[x].fa=0;Root=x;
		return dep;
	}
	int SpalyMax(){
		set_it p=--S.end();
		int x=(*p),dep=tree.Query(x,1,1,tot);
		if(x==Root)return 1;
		tree.Change(x,1);
		tree.Update(1,t[x].fa,1,1,1,tot);
		t[t[x].fa].ch[1]=t[x].ch[0];
		t[t[x].ch[0]].fa=t[x].fa;
		t[x].ch[0]=Root;t[Root].fa=x;
		t[x].fa=0;Root=x;
		return dep;
	}
	void DeleteRoot(){
		int x=Root;S.erase(Root);
		Root=t[x].ch[0]|t[x].ch[1];
		tree.Update(1,tot,-1,1,1,tot);
		t[x].ch[0]=t[x].ch[1]=0;
	}
	int DeleteMin(){int dep=SpalyMin();DeleteRoot();return dep;}
	int DeleteMax(){int dep=SpalyMax();DeleteRoot();return dep;}
}spaly;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		P[i].op=read();
		if(P[i].op==1){
			P[i].x=read();
			b[++tot]=P[i].x;
		}
	}
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1;i<=n;i++){
		if(P[i].op==1)P[i].x=lower_bound(b+1,b+tot+1,P[i].x)-b;
	}
	for(int i=1;i<=n;i++){
		if(P[i].op==1)printf("%d\n",spaly.Insert(P[i].x));
		if(P[i].op==2)printf("%d\n",spaly.SpalyMin());
		if(P[i].op==3)printf("%d\n",spaly.SpalyMax());
		if(P[i].op==4)printf("%d\n",spaly.DeleteMin());
		if(P[i].op==5)printf("%d\n",spaly.DeleteMax());
	}
	return 0;
}