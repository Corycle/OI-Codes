#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,tot,root;
struct Splay_Tree{
	struct Tree{
		int ch[2],fa;
		int num,sum,data;
	}t[N];
	void Pushup(int x){
		t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+t[x].num;
	}
	void Rotate(int x){
		int y=t[x].fa;int z=t[y].fa;
		int l=(x!=t[y].ch[0]);int r=l^1;
		if(z!=0){
			if(t[z].ch[0]==y)t[z].ch[0]=x;
			else t[z].ch[1]=x;
		}
		t[x].fa=z;t[y].fa=x;
		t[t[x].ch[r]].fa=y;
		t[y].ch[l]=t[x].ch[r];
		t[x].ch[r]=y;
		Pushup(y);Pushup(x);
	}
	void Splay(int x){
		while(t[x].fa){
			int y=t[x].fa;int z=t[y].fa;
			if(z!=0){
				if(x==t[y].ch[0]^y==t[z].ch[0])Rotate(x);
				else Rotate(y);
			}
			Rotate(x);
		}
		root=x;
	}
	void Find(int x){
		int p=root;
		while(p){
			if(x==t[p].data){
				Splay(p);
				return;
			}
			if(x<t[p].data)p=t[p].ch[0];
			else p=t[p].ch[1];
		}
	}
	void Insert(int x){
		int p=root,f=0;
		while(p){
			f=p;
			t[p].sum++;
			if(x==t[p].data){
				t[p].num++;
				return;
			}
			if(x<t[p].data)p=t[p].ch[0];
			else p=t[p].ch[1];
		}
		tot++;
		t[tot].data=x;
		t[tot].num=t[tot].sum=1;
		if(!root){root=tot;return;}
		if(x<t[f].data)t[f].ch[0]=tot;
		else t[f].ch[1]=tot;
		t[tot].fa=f;
		Splay(tot);
	}
	void Delete(int x){
		Find(x);
		int p=root;
		t[p].num--;t[p].sum--;
		if(t[p].num)return;
		int l=t[p].ch[0],r=t[p].ch[1];
		t[l].fa=t[r].fa=0;p=l;
		if(!l&&!r){root=0;return;}
		if(!l||!r){root=l+r;return;}
		while(t[p].ch[1])p=t[p].ch[1];
		Splay(p);
		t[p].ch[1]=r;t[r].fa=p;
		Pushup(r);Pushup(p);
	}
	int FIND(int k){
		int p=root;
		if(t[p].sum<k)return -1;
		while(p){
			if(t[t[p].ch[0]].sum+t[p].num>=k&&t[t[p].ch[0]].sum<k)return t[p].data;
			if(t[t[p].ch[0]].sum>=k)p=t[p].ch[0];
			else{
				k-=t[t[p].ch[0]].sum+t[p].num;
				p=t[p].ch[1];
			}
		}
	}
	int Ask(int x){
		Insert(x);
		int ans=t[t[root].ch[0]].sum;
		Delete(x);
		return ans;
	}
	int Pred(int x){
		int p=t[root].ch[0];
		if(!p)return -1;
		while(t[p].ch[1])p=t[p].ch[1];
		return t[p].data;
	}
	int Succ(int x){
		int p=t[root].ch[1];
		if(!p)return -1;
		while(t[p].ch[0])p=t[p].ch[0];
		return t[p].data;
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int op=read(),x=read();
		if(op==0)tree.Insert(x);
		if(op==1)tree.Delete(x);
		if(op==2)printf("%d\n",tree.FIND(x));
		if(op==3){
			tree.Insert(x);tree.Find(x);
			printf("%d\n",tree.t[tree.t[root].ch[0]].sum);
			tree.Delete(x);
		}
		if(op==4){
			tree.Insert(x);tree.Find(x);
			printf("%d\n",tree.Pred(x));
			tree.Delete(x);
		}
		if(op==5){
			tree.Insert(x);tree.Find(x);
			printf("%d\n",tree.Succ(x));
			tree.Delete(x);
		}
	}
	return 0;
}