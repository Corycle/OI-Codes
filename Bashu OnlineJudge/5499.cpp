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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,Ans,Pos,a[N],b[N];
struct Node{
	int l,r,val,pos;
	friend bool operator<(Node A,Node B){return A.val>B.val;}
};
struct Tree{int tag,Min,pos;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int x){t[p].Min=max(t[p].Min,x);t[p].tag=max(t[p].tag,x);}
	void Pushdown(int p){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);}
	void Pushup(int p){
		int l=p<<1,r=p<<1|1;t[p].Min=inf;t[p].pos=0;
		if(t[p].Min>t[l].Min){t[p].Min=t[l].Min;t[p].pos=t[l].pos;}
		if(t[p].Min>t[r].Min){t[p].Min=t[r].Min;t[p].pos=t[r].pos;}
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].Min=a[l];t[p].pos=l;return;};
		int mid=(l+r)>>1;Build(lson);Build(rson);
		Pushup(p);
	}
	void Update(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,z);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,z,lson);Update(x,y,z,rson);
		Pushup(p);
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			if(Ans>t[p].Min){Ans=t[p].Min;Pos=t[p].pos;}
			return;
		}
		int mid=(l+r)>>1;Pushdown(p);
		Query(x,y,lson);Query(x,y,rson);
	}
}tree;
void Query(int l,int r){
	Ans=inf;Pos=0;
	tree.Query(l,r,1,1,n);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	m=read();
	while(m--){
		int op=read(),x=read(),y=read(),k=read();
		if(op==1)tree.Update(x,y,k,1,1,n);
		if(op==2){
			int num=read();tot=0;
//			cout<<"======="<<endl;
			priority_queue<Node>q;
			Query(x,y);q.push((Node){x,y,Ans,Pos});
			while(num&&q.size()){
				Node A=q.top();q.pop();
				if(A.val>=k)break;b[++tot]=A.val;num--;
				if(A.l!=A.pos){Query(A.l,A.pos-1);q.push((Node){A.l,A.pos-1,Ans,Pos});}
				if(A.r!=A.pos){Query(A.pos+1,A.r);q.push((Node){A.pos+1,A.r,Ans,Pos});}
			}
			if(num)printf("-1\n");
			else{
				for(int i=1;i<=tot;i++)printf("%d ",b[i]);
				printf("\n");
			}
//			cout<<"======="<<endl;
		}
	}
	return 0;
}