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
const int N=5e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[N];
int n,K,Root[N];
struct Node{
	int l,r,pos,id;ll Ans;
	friend bool operator<(Node A,Node B){return A.Ans<B.Ans;}
};
priority_queue<Node>q;
struct Tree{int ch[2],sum,id;};
struct Trie{
	int tot;
	Tree t[N*35];
	void Insert(int &p,int y,int id,ll val){
		int x=++tot;t[x]=t[y];p=x;
		for(int i=32;i>=0;i--){
			int c=(val>>i)&1;
			t[x].ch[c]=++tot;
			x=t[x].ch[c];
			y=t[y].ch[c];
			t[x]=t[y];t[x].sum++;
		}
		t[x].id=id;
	}
	int Query(int x,int y,ll val){
		for(int i=32;i>=0;i--){
			int c=(val>>i)&1;
			int sum=t[t[y].ch[c^1]].sum-t[t[x].ch[c^1]].sum;
			if(sum){x=t[x].ch[c^1];y=t[y].ch[c^1];}
			else{x=t[x].ch[c];y=t[y].ch[c];}
		}
		return t[y].id;
	}
}tree;
void Insert(int l,int r,int id){
	int pos=tree.Query(Root[l-1],Root[r],a[id]);
	q.push((Node){l,r,pos,id,a[id]^a[pos]});
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read()+1;K=read();
	for(int i=2;i<=n;i++)a[i]=a[i-1]^read();
	for(int i=1;i<=n;i++)tree.Insert(Root[i],Root[i-1],i,a[i]);
	for(int i=1;i<=n;i++)Insert(1,i,i);
	ll ans=0;
	while(q.size()&&K--){
		Node A=q.top();q.pop();ans+=A.Ans;
		if(A.l<A.pos)Insert(A.l,A.pos-1,A.id);
		if(A.r>A.pos)Insert(A.pos+1,A.r,A.id);
	}
	printf("%lld",ans);
	return 0;
}